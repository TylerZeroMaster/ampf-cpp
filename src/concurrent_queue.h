/*
 *   This file is part of ampf-cpp which demonstrates one 
 *   implementation of a concurrent queue by finding Mersenne prime numbers
 *   Copyright (C) 2021  Tyler Nullmeier
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __CONCURRENT_QUEUE__
#define __CONCURRENT_QUEUE__

#include <deque>			// std::deque
#include <exception>		// std::exception
#include <mutex>			// std::mutex

#include "exceptions.h"		// cancellation_token, queue_closed
#include "utils.h"			// find_element
#include "my_promise.h"		// my_promise

template <typename T>
class concurrent_queue 
{
public:
	explicit concurrent_queue(unsigned int max_size) : max_size(max_size), closed(false) 
	{
		
	}
	
	inline bool empty() noexcept
	{
		return queue.size() == 0;
	}
	
	inline bool full() noexcept
	{
		return max_size == 0 ? false : queue.size() >= max_size;
	}
	
	void push_back(T item)
	{
		L.lock();
		
		if(closed)
		{
			L.unlock();
			throw queue_closed();
		}
		
		if(full())
		{
			my_promise<bool> putter;
			auto fut = putter.get_future();
			putters.push_back(&putter);
			
			try
			{
				L.unlock();
				fut.get();
				L.lock();
			}
			catch(std::exception& e)
			{
				L.lock();
				auto it = putters.cbegin();
				if(find_element(it, putters.cend(), &putter))
				{
					putters.erase(it);
				}
				L.unlock();
				
				throw e;
			}
		}
		
		while(getters.size() > 0)
		{
			auto prom = getters.front();
			getters.pop_front();
			if(!prom->is_done())
			{
				prom->set_result(item);
				L.unlock();
				return;
			}
		}
		queue.push_back(item);
		
		L.unlock();
	}
	
	T pop_front()
	{
		T result;
		L.lock();
		
		if(closed)
		{
			L.unlock();
			throw queue_closed();
		}
		
		if(empty())
		{
			my_promise<T> getter;
			auto fut = getter.get_future();
			getters.push_back(&getter);
			
			try
			{
				L.unlock();
				result = fut.get();
				L.lock();
			}
			catch(std::exception& e)
			{
				// Consider adding catch for cancellation_token that does not
				// remove the promise. Instead, remove promise in the close()
				// method (after it is cancelled)
				L.lock();
				auto it = getters.cbegin();
				if(find_element(it, getters.cend(), &getter))
				{
					getters.erase(it);
				}
				L.unlock();
				
				throw e;
			}
		}
		else
		{
			result = queue.front();
			queue.pop_front();
		}
		
		while(putters.size() > 0)
		{
			auto prom = putters.front();
			putters.pop_front();
			if(!prom->is_done())
			{
				prom->set_result(true);
				break;
			}
		}
		
		L.unlock();
		
		return result;
	}
	
	void close() noexcept
	{
		L.lock();
		for(auto prom : getters)
			prom->cancel();
		for(auto prom : putters)
			prom->cancel();
		closed = true;
		L.unlock();
	}

	bool is_closed() noexcept
	{
		return closed;
	}
	
protected:
	unsigned int max_size;
	bool closed;
	std::deque<my_promise<T>*> getters;
	std::deque<my_promise<bool>*> putters;
	std::deque<T> queue;
	std::mutex L;
};

#endif // __CONCURRENT_QUEUE__
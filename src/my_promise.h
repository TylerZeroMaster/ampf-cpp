/*
 *   This file is part of concurrent_queue_ex which demonstrates one 
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

#ifndef __MY_PROMISE__
#define __MY_PROMISE__

#include <future>			// std::promise

template <typename T>
class my_promise : public std::promise<T>
{
public:
	explicit my_promise() : done(false), cancelled(false) { }

	void set_result(T item)
	{
		this->set_value(item);
		done = true;
	}
	
	void cancel()
	{
		auto p = std::make_exception_ptr(cancellation_token());
		this->set_exception(p);
		done = true;
		cancelled = true;
	}
	
	bool is_done() noexcept
	{
		return done;
	}
	
	bool is_cancelled() noexcept
	{
		return cancelled;
	}
	
protected:
	bool done;
	bool cancelled;
};

#endif // __MY_PROMISE__
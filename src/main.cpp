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

#include <functional>		// std::ref
#include <iostream>			// std::cout, std::endl
#include <thread>			// std::thread

#include <gmpxx.h>			// mpz_class
#include "concurrent_queue.h"

using std::cout;
using std::endl;

typedef unsigned int uint;

const mpz_class ZERO = 0;
const mpz_class ONE = 1;
const mpz_class TWO = 2;
const mpz_class FOUR = 4;

bool is_prime(uint p)
{
	for(uint i = 2; i * i <= p; i++) 
	{
		if(p%i == 0)
		{
			return false;
		}
	}
	return true;
}

bool LLT(uint p, mpz_class& least_sig_mask, mpz_class& s, mpz_class& remaining_bits)
{
	const uint repeat_count = p - 2;
	
	least_sig_mask = (ONE<<p) - 1;
	s = FOUR;
	
	for(uint i = 0; i < repeat_count; i++)
	{
		s *= s;
		s -= TWO;
		
		remaining_bits = s>>p;
		
		while(remaining_bits != ZERO)
		{
			s &= least_sig_mask;
			s += remaining_bits;
			
			remaining_bits = s>>p;
		}
	}
	
	return s == least_sig_mask;
}

void producer(concurrent_queue<uint>& input)
{
	uint p = 3;
	while(true)
	{
		try
		{
			for(; !is_prime(p); p += 2);
			input.push_back(p);
			p += 2;
		}
		catch(std::exception& e)
		{
			break;
		}
	}
}

void worker(concurrent_queue<uint>& input, concurrent_queue<uint>& output)
{
	uint n;
	mpz_class least_sig_mask, s, remaining_bits;
	while(true)
	{
		try
		{
			n = input.pop_front();
			if(LLT(n, least_sig_mask, s, remaining_bits))
			{
				output.push_back(n);
			}
		}
		catch (std::exception& ex)
		{
			break;
		}
	}
}

uint CPU_count() noexcept 
{
	const uint count = std::thread::hardware_concurrency();
	return count > 0 ? count : 4; // default to 4
}

int stoi(const char* s, uint r)
{
	int ret = 0;
	char b;
	uint ax = r;
	auto start = s;
	
	for(; *s != '\0'; s++);
	
	while(s != start)
	{
		s--;
		b = *s ^ 0x30;
		if(b < 10)
		{
			break;
		}
	}
	
	if(s == start)
	{
		return 0;
	}
	
	ret = b;
	
	while(s != start)
	{
		s--;
		b = *s ^ 0x30;
		if(b > 10)
		{
			if(s == start && *s == '-')
			{
				return -1 * ret;
			}
			continue;
		}
		ret += b * ax;
		ax *= r;
	}
	
	return ret;
}

int main(int argc, const char** argv)
{
	const uint thread_count = CPU_count() * 2;
	std::thread threads[thread_count + 1];
	concurrent_queue<uint> input(thread_count * 2);
	concurrent_queue<uint> output(thread_count);
	uint mprime_count = 100;
	
	if(argc > 1)
	{
		int count = stoi(argv[1], 10);
		if(count > 0)
		{
			mprime_count = count;
		}
	}
	
	threads[0] = std::thread(producer, std::ref(input));
	for(uint i = 0; i < thread_count; i++)
	{
		threads[i + 1] = std::thread(worker, std::ref(input), std::ref(output));
	}
	
	for(int i = mprime_count; i --> 0;)
	{
		cout<<output.pop_front()<<endl;
	}
	
	input.close();
	output.close();
	
	for(auto& th : threads) th.join();

	return 0;
}
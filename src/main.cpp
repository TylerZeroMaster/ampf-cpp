#include <functional>		// std::ref
#include <iostream>			// std::cout, std::endl
#include <thread>			// std::thread

#include "concurrent_queue.h"

using std::cout;
using std::endl;

typedef unsigned int uint;

void producer(concurrent_queue<uint>& input)
{
	for(uint x = 0 ; x < 100; x++)
	{
		try
		{
			input.push_back(x);
		}
		catch (std::exception& ex)
		{
			break;
		}
	}
}

void worker(concurrent_queue<uint>& input, concurrent_queue<uint>& output)
{
	uint next;
	while(true)
	{
		try
		{
			next = input.pop_front();
			output.push_back(++next * 2);
		}
		catch (std::exception& ex)
		{
			break;
		}
	}
}

int main()
{
	const uint thread_count = 4 * 2;
	std::thread threads[thread_count + 1];
	concurrent_queue<uint> input(thread_count * 2);
	concurrent_queue<uint> output(thread_count);
	
	cout<<"Starting..."<<endl;
	threads[0] = std::thread(producer, std::ref(input));
	for(uint i = 0; i < thread_count; i++)
	{
		threads[i + 1] = std::thread(worker, std::ref(input), std::ref(output));
	}
	cout<<"Waiting for output..."<<endl;
	
	for(int i = 100; i --> 0;)
	{
		cout<<output.pop_front()<<endl;
	}
	cout<<"Closing..."<<endl;
	
	input.close();
	output.close();
	
	for(auto& th : threads) th.join();

	return 0;
}
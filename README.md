# AMPF-CPP (Another Mersenne Prime Finder-CPP)

## About
This program finds [Mersenne prime numbers](https://en.wikipedia.org/wiki/Mersenne_prime) in the sequence discovered starting at three. It accomplishes this with the help of [The GNU Multiple Precision Arithmetic Library.](https://gmplib.org/) I made this program so that I would become more familiar with multi-threading in C++. It utilizes my implementations of a concurrent queue and an [optimized modulo](https://en.wikipedia.org/wiki/Lucas%E2%80%93Lehmer_primality_test#Time_complexity) operation.

## Usage
```
ampf-cpp [number of Mersenne prime exponents to find]
```

You can also see src/main.cpp for examples of using the `concurrent_queue` class.

## Conclusion
Prior to this project I had only used the high-level async/await interfaces in JavaScript, Python, and C# and channels in Go (golang). This project showed me that using a mutex for exclusive memory access and futures for synchronizing threads is VERY similar to async/await. Consequently, the following two examples of methods that add items to a concurrent list are very similar:

### C++ example (Taken from src/concurrent_queue.h)
```cpp
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
```

### JavaScript example (Taken from my async queue JS class)
```js
async push(item) 
{
	if(this.closed) {
		throw new Error('Queue Closed');
	}
	
	if(this.full()) {
		const tcs = new TaskCompletionSource();
		this.writeWaiters.push(tcs);
		
		try {
			await tcs.task;
		} catch(e) {
			const tcsIndex = this.writeWaiters.findIndex(t => t === tcs);
			if(tcsIndex !== -1) {
				this.writeWaiters.splice(tcsIndex, 1);
			}
			
			throw e;
		}
	}
	
	if(this.readWaiters.length > 0) {
		const tcs = this.readWaiters.shift();
		tcs.setResult(item);
	} else 	{
		this.collection.push(item);
	}
}
```

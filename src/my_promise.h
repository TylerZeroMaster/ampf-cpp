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
#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>	// std::exception

class cancellation_token : public std::exception {
public:
	const char* what() const noexcept;
};

class queue_closed : public std::exception {
public:
	const char* what() const noexcept;
};

#endif // __EXCEPTIONS_H__
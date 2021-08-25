#ifndef __EXCPTIONS_H__
#define __EXCPTIONS_H__

#include <exception>	// std::exception

class cancellation_token : public std::exception {
public:
	const char* what() const noexcept;
};

class queue_closed : public std::exception {
public:
	const char* what() const noexcept;
};

#endif
#include "exceptions.h"

const char* cancellation_token::what() const noexcept 
{ 
	return "Promise cancelled."; 
}

const char* queue_closed::what() const noexcept 
{ 
	return "Tried to use a closed queue."; 
}
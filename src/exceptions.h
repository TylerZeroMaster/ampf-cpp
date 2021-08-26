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
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

#include "exceptions.h"

const char* cancellation_token::what() const noexcept 
{ 
	return "Promise cancelled."; 
}

const char* queue_closed::what() const noexcept 
{ 
	return "Tried to use a closed queue."; 
}
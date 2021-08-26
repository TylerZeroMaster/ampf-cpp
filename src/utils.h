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

#ifndef __UTILS_H__
#define __UTILS_H__

template<typename IT, typename T>
inline
bool find_element(IT& it, const IT end, const T element) noexcept
{
	for(; it != end; it++)
	{
		if(*it == element)
		{
			return true;
		}
	}
	return false;
}

#endif // __UTILS_H__
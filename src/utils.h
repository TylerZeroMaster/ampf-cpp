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

#endif
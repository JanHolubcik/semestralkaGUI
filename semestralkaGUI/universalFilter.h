#pragma once

template<typename T>
class universalFilter
{
public:
	universalFilter() {};
	virtual ~universalFilter() {};

	virtual bool matchesFilter(T o) = 0;
};


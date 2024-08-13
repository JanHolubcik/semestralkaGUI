#pragma once
#include "universalFilter.h";
#include "./structures/list/array_list.h";
template<typename T>
class compositeFilter 
{
private:
	structures::ArrayList<universalFilter<T>*>* filters = new structures::ArrayList< universalFilter<T>*>();
public:
	compositeFilter() {};
	~compositeFilter() {
		for (auto item : *filters) {
			delete item;
		}
		delete filters;
	};
	structures::ArrayList<universalFilter<T>*>* getFilters() {
		return *filters;
	}

void addFilter(universalFilter<T>* newFilterP) {
	universalFilter<T>* newFilter = newFilterP;
	filters->add(newFilter);
	}

bool matchesFilterAnd(T o) {
	for (auto item: *filters)
	{
		if (!item->matchesFilter(o)) {
			return false;
		}
	}
	return true;
};
bool matchesFilterOr(T o) {
	for (auto item : *filters)
	{
		if (item->matchesFilter(o)) {
			return true;
		}
	}
	return false;
};
};


#pragma once
#include "criterio.h"
#include "universalFilter.h"
template<typename K, typename T, typename V>
class filter:public universalFilter<typename T>
{
public:
	filter(){}
	filter(criterio<V, T>* criterioP):
	criterioFilter(criterioP) {
	
	};

	~filter() {
		delete criterioFilter;
	};

protected:
	criterio<V, T>* getCriterio(){
		return *criterioFilter;
	}
	criterio<V, T>* criterioFilter=nullptr;

	
};

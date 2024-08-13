#pragma once
#include "structures/uzemnaJednotka/uzemnaJednotka.h"
#include "filter.h"
#include "criterio.h"
template<typename K, typename T, typename V>
class fUJByValue:public filter<K,T,V>
{
	V value;
public:
	fUJByValue() {};
	fUJByValue(criterio<V, T>* criterioP,V valueP ):
		value(valueP){
		this->criterioFilter = criterioP;
	};
	~fUJByValue() {
	//	delete criterioFilter;
	};
	bool matchesFilter(T o) override {
		return value == this->criterioFilter->evaluate(o);
	};
};


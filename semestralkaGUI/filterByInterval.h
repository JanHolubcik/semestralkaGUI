#pragma once
template<typename K, typename T, typename V>
class filterByInterval :public filter<K, T, V>
{
	V minV;
	V maxV;
public:
	filterByInterval() {};
	~filterByInterval() {};
	filterByInterval(criterio<V, T>* criterioP, V minP, V maxP) :
		minV(minP),
		maxV(maxP) {
		this->criterioFilter = criterioP;
	};
	bool matchesFilter(T o) override {
		return minV< this->criterioFilter->evaluate(o) && maxV > this->criterioFilter->evaluate(o);
	};
};


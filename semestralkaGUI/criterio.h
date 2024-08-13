#pragma once
template<typename T, typename O>
class criterio
{
public:
	virtual T evaluate(O o) = 0;
	criterio(){};
	~criterio(){};
};


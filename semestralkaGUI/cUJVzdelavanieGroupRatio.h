#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
#include <string>
class cUJVzdelavanieGroupRatio :
	public criterioUJ<double>
{
	int vzdelavanie;
public:
	cUJVzdelavanieGroupRatio(int vzdelavanie) :
		vzdelavanie(vzdelavanie) {};
	~cUJVzdelavanieGroupRatio() {};
	double evaluate(uzemnaJednotka* b) override {
		int vzSum = 0;
		for (int i = 0; i < b->getVzdelavanie().size(); i++)
		{
			vzSum = vzSum + b->getVzdelavanie().at(i);
		}
		return (100 * ((double)b->getVzdelavanie().at(vzdelavanie)) / (double)vzSum);
	};
};


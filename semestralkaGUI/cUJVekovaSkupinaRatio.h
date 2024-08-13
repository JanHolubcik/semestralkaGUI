#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
#include <string>
class cUJVekovaSkupinaRatio :
		public criterioUJ<double>
{
	int vekovaSkupina;
public:
	cUJVekovaSkupinaRatio(int vekovaSkupina) :
		vekovaSkupina(vekovaSkupina) {};
	~cUJVekovaSkupinaRatio() {};
	double evaluate(uzemnaJednotka* b) override {
		size_t vzSum = 0;
		for (size_t i = 0; i < b->getVzdelavanie().size(); i++)
		{
			vzSum = vzSum + b->getVzdelavanie().at(i);
		}
		return 100 * (b->getVzdelavanie().at(vekovaSkupina)+(b->getVzdelavanie().at(vekovaSkupina +3))) / (double)vzSum;
	};
};
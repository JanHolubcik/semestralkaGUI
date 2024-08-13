#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
#include <string>
class cUJVekovaSkupina :
	public criterioUJ<int>
{
	int vekSkupina;
public:
	cUJVekovaSkupina(int vekSkupina) :
		vekSkupina(vekSkupina) {};
	~cUJVekovaSkupina() {};
	int evaluate(uzemnaJednotka* b) override {
		return b->getVekovaSkupina().at(vekSkupina)+ b->getVekovaSkupina().at(vekSkupina+3);
	};
};
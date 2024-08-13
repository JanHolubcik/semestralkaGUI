#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
#include <string>
class kUJVzdelavanieSum:
	public criterioUJ<int>
{
	int vzdelavanie;
public:
	kUJVzdelavanieSum(int vzdelavanie):
	vzdelavanie(vzdelavanie) {};
	~kUJVzdelavanieSum() {};
	int evaluate(uzemnaJednotka* b) override {
		return b->getVzdelavanie().at(vzdelavanie);
	};
};


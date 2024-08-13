#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
#include <string>

class criterioName:
	public criterioUJ<std::wstring>
{
public:
	criterioName(){};
	~criterioName(){};
	std::wstring evaluate(uzemnaJednotka* b) override {
		return b->getOfficialTitle();
	};
};




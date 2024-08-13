#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
#include "criterioUJ.h"
class cType :
	public criterioUJ<int>
{
public:
	cType() {};
	~cType() {};
	int evaluate(uzemnaJednotka* b) override {
		return b->getType();
	};
};


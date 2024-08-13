#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
#include <string>
#include "criterioUJ.h"
class cBelongsTo :
	public criterioUJ<bool>
{
	uzemnaJednotka* UJ;
public:
	cBelongsTo(uzemnaJednotka* UJ) :
		UJ(UJ) {};
	~cBelongsTo() {};
	bool evaluate(uzemnaJednotka* b) override {
		if (!b->getBelongsTo()) {
			return false;
		}
		if (!b->getBelongsTo()->getBelongsTo()) {
			return false;
		}
	
		if (b->getBelongsTo() == UJ|| b->getBelongsTo()->getBelongsTo()==UJ) {
			return true;
		}
		return false;
	};
};
#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
template<typename T>
class criterioUJ:public criterio<T, uzemnaJednotka* >
{
public:
	~criterioUJ() {

	}
};


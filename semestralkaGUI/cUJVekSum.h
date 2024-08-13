#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
#include <string>
class cUJVekGroupSum :
	public criterioUJ<int>
{
	int pohlavie;
	int from;
	int to;
public:
	cUJVekGroupSum(int pohlavie, int from, int to) :
		pohlavie(pohlavie),
		from(from),
		to(to) {};
	~cUJVekGroupSum() {};
	int evaluate(uzemnaJednotka* b) override {
		int sum = 0;
		if (pohlavie == -1) {
			for (size_t i = from; i < to; i++)
			{
				sum += b->getVek().at(i) + b->getVek().at(i + 101);
			}

		}
		else {

			for (size_t i = from; i < to; i++)
			{
				sum += b->getVek().at(i + (101 * pohlavie));
			}
		}
		return sum;
	};
};


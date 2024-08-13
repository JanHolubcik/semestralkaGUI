#pragma once
#include "criterio.h"
#include "./structures/uzemnaJednotka/uzemnaJednotka.h"
#include <string>
class cUJVekRatio :
	public criterioUJ<double>
{
	int pohlavie;
	int from;
	int to;
public:
	cUJVekRatio(int pohlavie,int from, int to):
		pohlavie(pohlavie),
		from(from),
		to(to)
	{};
	~cUJVekRatio() {};
	double evaluate(uzemnaJednotka* b) override {
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

		size_t vzSum = 0;
		for (size_t i = 0; i < b->getVekovaSkupina().size(); i++)
		{
			vzSum = vzSum + b->getVekovaSkupina().at(i);
		}
		return 100 * (sum) / (double)vzSum;
	
	};
};


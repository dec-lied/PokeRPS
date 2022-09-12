#include "RPS.h"

unsigned RPS::ownType, RPS::opponentType;

void RPS::seed()
{
	srand((unsigned)time(0));
}

unsigned RPS::calcWinner()
{
	RPS::opponentType = rand() % 3;

	switch (RPS::ownType)
	{
	case 0: // fire
		if (RPS::opponentType == 2)
			return 0;
		else if (RPS::opponentType == 1)
			return 1;
		else
			return 2;

	case 1: // water
		if (RPS::opponentType == 0)
			return 0;
		else if (RPS::opponentType == 2)
			return 1;
		else
			return 2;

	case 2: // grass
		if (RPS::opponentType == 1)
			return 0;
		else if (RPS::opponentType == 0)
			return 1;
		else
			return 2;

	default:
#ifdef _DEBUG
		std::cout << "??? in rps" << std::endl;
#endif
		return -1;
	}
}
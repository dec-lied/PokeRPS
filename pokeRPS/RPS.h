#pragma once

#include <string>
#include <random>

#ifdef _DEBUG
#include <iostream>
#endif

class RPS
{
public:
	static unsigned ownType, opponentType;

	// sets seed to current time
	static void seed();
	/* return values:
	* 0: player won
	* 1: opponent won
	* 2: tie 
	* -1: oops */
	static unsigned calcWinner();
};
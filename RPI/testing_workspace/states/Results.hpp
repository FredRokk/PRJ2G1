#ifndef RESULTS
#define RESULTS

#include "State.hpp"
#include "Idle.hpp"
#include "PlayerOneHighscore.hpp"
#include "PlayerTwoHighscore.hpp"
#include "GameThreadFunctor.hpp"

class Results: public State
{
public:
	Results(GameThreadFunctor* gameTF, int selectedMap, int playerOnePoints, int playerTwoPoints);
	~Results();
	void fire();

private:
	int selectedMap_;
	int playerOnePoints_;
	int playerTwoPoints_;
	int scoreToBeat_ = 400; //should be initialized in constructor and gotten from Gamerules function.
};

#endif
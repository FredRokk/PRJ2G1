#ifndef RESULTS
#define RESULTS

#include "states/State.hpp"
#include "states/Idle.hpp"
#include "states/PlayerOneHighscore.hpp"
#include "states/PlayerTwoHighscore.hpp"
#include "threadFunctors/GameThreadFunctor.hpp"
#include "communication/Messages.hpp"
#include "gameSpecifics/Gamerules.hpp"

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
	int scoreToBeat_ = 100; //should be initialized in constructor and gotten from Gamerules function.
};

#endif
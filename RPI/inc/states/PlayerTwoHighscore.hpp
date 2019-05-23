#ifndef PLAYER_TWO_HIGHSCORE
#define PLAYER_TWO_HIGHSCORE

#include "states/State.hpp"
#include "states/Idle.hpp"
#include "threadFunctors/GameThreadFunctor.hpp"

class PlayerTwoHighscore: public State
{
public:
	PlayerTwoHighscore(GameThreadFunctor* gameTF, int selectedMap, int playerTwoPoints);
	~PlayerTwoHighscore();
	void fire();
	void up();
	void down();

private:
	std::string name;
	int selectedMap_;
	int playerTwoPoints_;
	int currentChar = 0;
};

#endif
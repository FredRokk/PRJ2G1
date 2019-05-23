#ifndef PLAYER_ONE_HIGHSCORE
#define PLAYER_ONE_HIGHSCORE

#include "State.hpp"
#include "Idle.hpp"
#include "PlayerTwoHighscore.hpp"
#include "GameThreadFunctor.hpp"

class PlayerOneHighscore: public State
{
public:
	PlayerOneHighscore(GameThreadFunctor* gameTF, int selectedMap, int playerOnePoints, int playerTwoPoints);
	~PlayerOneHighscore();
	void fire();
	void up();
	void down();

private:
	std::string name;
	int selectedMap_;
	int playerOnePoints_;
	int playerTwoPoints_;
	int currentChar = 0;
};

#endif
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
	std::string name_ = "AAA";
	int selectedMap_;
	int playerTwoPoints_;
	int currentChar_ = 0;
	int currentCharIndex_ = 0;
	std::string charList_ = "ABCDEFGIHJKLMNOPQRSTUVWXYZ1234567890";

	void cycleCurrentCharIndex(bool increase);
	char getCharFromList(int index);
};

#endif
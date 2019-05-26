#ifndef PLAYER_ONE_HIGHSCORE
#define PLAYER_ONE_HIGHSCORE

#include "states/State.hpp"
#include "states/Idle.hpp"
#include "states/PlayerTwoHighscore.hpp"
#include "threadFunctors/GameThreadFunctor.hpp"
#include "communication/Messages.hpp"

class PlayerOneHighscore: public State
{
public:
	PlayerOneHighscore(GameThreadFunctor* gameTF, int selectedMap, int playerOnePoints, int playerTwoPoints);
	~PlayerOneHighscore();
	void fire();
	void up();
	void down();

private:
	std::string name_ = "AAA";
	int selectedMap_;
	int playerOnePoints_;
	int playerTwoPoints_;
	int currentChar_ = 0;
	int currentCharIndex_ = 0;
	std::string charList_ = "ABCDEFGIHJKLMNOPQRSTUVWXYZ1234567890";

	void cycleCurrentCharIndex(bool increase);
	char getCharFromList(int index);
};

#endif
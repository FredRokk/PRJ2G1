#ifndef IDLE
#define IDLE

#include "states/State.hpp"
#include "states/MapSelect.hpp"
#include "threadFunctors/GameThreadFunctor.hpp"
#include "communication/Messages.hpp"
#include "gameSpecifics/Gamerules.hpp"

class Idle: public State
{
public:
	Idle(GameThreadFunctor* gameTF);
	~Idle();
	void left();
	void right();
	void onePlayer();
	void twoPlayer();
private:
	int currentIdle_ = 1;
};

#endif
#ifndef IDLE
#define IDLE

#include "states/State.hpp"
#include "states/MapSelect.hpp"
#include "threadFunctors/GameThreadFunctor.hpp"

class Idle: public State
{
public:
	Idle(GameThreadFunctor* gameTF);
	~Idle();
	void left();
	void right();
	void onePlayer();
	void twoPlayer();
};

#endif
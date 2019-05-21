#ifndef IDLE
#define IDLE

#include "State.hpp"
#include "MapSelect.hpp"
#include "GameThreadFunctor.hpp"

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
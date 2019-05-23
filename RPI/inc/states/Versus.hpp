#ifndef VERSUS
#define VERSUS

#include "states/State.hpp"
#include "states/Idle.hpp"
#include "states/Results.hpp"
#include "threadFunctors/GameThreadFunctor.hpp"

class Versus: public State
{
public:
	Versus(GameThreadFunctor* gameTF, int selectedMap);
	~Versus();
	void up();
	void down();
	void left();
	void right();
	void fire();
	void hit(int field);

private:
	int selectedMap_;
	//Map map
	int playerOnePoints_ = 0;
	int playerTwoPoints_ = 0;
	int totalShots = 0;
	int maxShots; //INITIALIZE THIS in CTOR TO SOMETHING IN GameRules
};

#endif
#ifndef VERSUS
#define VERSUS

#include "states/State.hpp"
#include "states/Idle.hpp"
#include "states/Results.hpp"
#include "threadFunctors/GameThreadFunctor.hpp"
#include "communication/Messages.hpp"
#include "gameSpecifics/Gamerules.hpp"
#include "gameSpecifics/Map.hpp"

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
	Map map_;
	int player1Points_ = 0;
	int player2Points_ = 0;
	int player1Shots_;
	int player2Shots_;
	int currentPlayer_ = 1;
	int maxShots; //INITIALIZE THIS in CTOR TO SOMETHING IN GameRules
};

#endif
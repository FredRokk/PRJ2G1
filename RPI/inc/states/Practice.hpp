#ifndef PRACTICE
#define PRACTICE

#include "states/State.hpp"
#include "states/Idle.hpp"
#include "threadFunctors/GameThreadFunctor.hpp"
#include "communication/Messages.hpp"
#include "gameSpecifics/Gamerules"
#include "gameSpecifics/Map"

class Practice: public State
{
public:
	Practice(GameThreadFunctor* gameTF, int selectedMap);
	~Practice();
	void fire();
	void hit(int field);

private:
	int selectedMap_;
	Map map_;
};

#endif
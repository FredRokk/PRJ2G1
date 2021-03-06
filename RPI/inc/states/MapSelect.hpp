#ifndef MAP_SELECT
#define MAP_SELECT

#include "states/State.hpp"
#include "states/Idle.hpp"
#include "states/Versus.hpp"
#include "states/Practice.hpp"
#include "threadFunctors/GameThreadFunctor.hpp"
#include "communication/Messages.hpp"
#include "gameSpecifics/Gamerules.hpp"

class MapSelect: public State
{
public:
	MapSelect(GameThreadFunctor* gameTF, bool multiplayer);
	~MapSelect();
	void up();
	void down();
	void fire();

private:
	bool multiplayer_;
	int currentMap_ = 1;
	void changeMap(bool increase);
};

#endif
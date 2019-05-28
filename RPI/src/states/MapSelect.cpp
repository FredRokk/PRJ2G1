#include <iostream>

#include "states/MapSelect.hpp"

/* 
class: MapSelect
Implementation of the MapSelect State's member functions
*/

MapSelect::MapSelect(GameThreadFunctor* gameTF, bool multiplayer){
	multiplayer_ = multiplayer;
	this->gameTF = gameTF;
	menuName_ = "mapSelect";

	sendChangeMapInd(gameTF->getPrintMq(), currentMap_);
	sendShowInd(gameTF->getPrintMq(), menuName_);
}

MapSelect::~MapSelect(){
	sendCleanInd(gameTF->getPrintMq(), menuName_);
}

void MapSelect::up(){
	changeMap(false);
	sendChangeMapInd(gameTF->getPrintMq(), currentMap_);
}

void MapSelect::down(){
	changeMap(true);
	sendChangeMapInd(gameTF->getPrintMq(), currentMap_);
}

void MapSelect::fire(){
	if(returning_){
		std::cout << "MapSelect: fire - Returning to was true, going back to idle" << std::endl;
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	}
	else if(multiplayer_){
		gameTF->setCurrent(new Versus(this->gameTF, currentMap_));
		delete this;
	} else {
		gameTF->setCurrent(new Practice(this->gameTF, currentMap_));
		delete this;
	}
}

void MapSelect::changeMap(bool increase){
	if(increase){
		currentMap_++;
	} else {
		currentMap_--;
	}

	if (currentMap_ < 1) currentMap_ = NUMBER_OF_DEFAULT_MAPS + 1;
	else if (currentMap_ > NUMBER_OF_DEFAULT_MAPS + 1) currentMap_ = 1;
}
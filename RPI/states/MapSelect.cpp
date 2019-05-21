#include <iostream>

#include "MapSelect.hpp"

/* 
class: MapSelect
Implementation of the MapSelect State's member functions
*/

MapSelect::MapSelect(GameThreadFunctor* gameTF, bool multiplayer){
	multiplayer_ = multiplayer;
	this->gameTF = gameTF;
	std::cout << "MapSelect: ctor - fire to enter new state" << std::endl;
}

MapSelect::~MapSelect(){
	std::cout << "MapSelect: dtor" << std::endl;
}

void MapSelect::up(){
	std::cout << "MapSelect: up" << std::endl;
	currentMap_++;
	if (currentMap_ > 3) currentMap_ = 1;
	std::cout << "Current Map: " << currentMap_ << std::endl;
}

void MapSelect::down(){
	std::cout << "MapSelect: down" << std::endl;
	currentMap_--;
	if (currentMap_ < 1) currentMap_ = 3;
	std::cout << "Current Map: " << currentMap_ << std::endl;
}

void MapSelect::fire(){
	if(returning_){
		std::cout << "MapSelect: fire - Returning to was ture, going back to idle" << std::endl;
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	}
	else if(multiplayer_){
		std::cout << "MapSelect: fire - Entering versus with map: " << currentMap_ << std::endl;
		gameTF->setCurrent(new Versus(this->gameTF, currentMap_));
		delete this;
	} else {
		std::cout << "MapSelect: fire - Entering practice with map: " << currentMap_ << std::endl;
		gameTF->setCurrent(new Practice(this->gameTF, currentMap_));
		delete this;
	}
}
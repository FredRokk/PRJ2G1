#include <iostream>

#include "states/Versus.hpp"

/* 
class: Versus
Implementation of the Versus State's member functions
*/

Versus::Versus(GameThreadFunctor* gameTF, int selectedMap){
	selectedMap_ = selectedMap;
	this->gameTF = gameTF;

	menuName_ = "versus";
	map_ = Gamerules::generateMap(selectedMap_);

	sendMapInd(gameTF->getCommMq(), map_.getMapString());
	sendShowInd(gameTF->getPrintMq(), menuName_);
	std::cout << "Versus: ctor - fire to enter new state" << std::endl;
}

Versus::~Versus(){
	std::cout << "Versus: dtor" << std::endl;
}

void Versus::up(){
	std::cout << "Versus: up" << std::endl;
}

void Versus::down(){
	std::cout << "Versus: down" << std::endl;
}

void Versus::left(){
	std::cout << "Versus: left" << std::endl;
}

void Versus::right(){
	std::cout << "Versus: right" << std::endl;
}

void Versus::fire(){
	if (returning_) {
		std::cout << "Versus: fire - Returning was true, returning to Idle" << std::endl;
		gameTF->setCurrent(new Idle(this->gameTF));
		delete this;
	}
	else {
		std::cout << "Versus: fire - Awarding magic number of points, playerOnePoints = 350, playerTwoPoints = 450, entering result" << std::endl;
		playerOnePoints_ = 350;
		playerTwoPoints_ = 450;
		gameTF->setCurrent(new Results(this->gameTF, selectedMap_, playerOnePoints_, playerTwoPoints_));
		delete this;
	}
}

void Versus::hit(int field){
	std::cout << "Versus: hit" << std::endl;
}

#include <iostream>

#include "State.hpp"

/* 
class: State
Implementation of the State interface's member functions
*/

State::~State(){
	std::cout << "Default: dtor" << std::endl;
}

void State::up(){
	std::cout << "Default: up" << std::endl;
}

void State::down(){
	std::cout << "Default: down" << std::endl;
}
void State::left(){
	std::cout << "Default: left" << std::endl;
}
void State::right(){
	std::cout << "Default: right" << std::endl;
}
void State::onePlayer(){
	std::cout << "Default: onePlayer" << std::endl;
}
void State::twoPlayer(){
	std::cout << "Default: twoPlayer" << std::endl;
}
void State::back(){
	std::cout << "Default: back" << std::endl;
	if(returning_){
		std::cout << "Default: back - returning is true, setting returning to false" << std::endl;
		returning_ = false;
	} else {
		std::cout << "Default: back - setting return to true" << std::endl;
		returning_ = true;
	}
}
void State::fire(){
	std::cout << "Default: fire" << std::endl;
}
void State::hit(int field){
	std::cout << "Default: hit" << std::endl;
}

void State::miss(){
	std::cout << "Default: miss" << std::endl;
}
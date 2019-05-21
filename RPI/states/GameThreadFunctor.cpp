#include <iostream>
#include <string>
#include "GameThreadFunctor.hpp"

GameThreadFunctor::GameThreadFunctor(){
	state = new Idle(this);
}

void GameThreadFunctor::setCurrent(State* s){
	state = s;
}

void GameThreadFunctor::takeCommand(){
	//This method is for testing purposes only
	std::string cmd;
	std::cin >> cmd;

	if (cmd == "up"){
		state->up();
	} else if (cmd == "down"){
		state->down();
	} else if (cmd == "left"){
		state->left();
	} else if (cmd == "right"){
		state->right();
	} else if (cmd == "onePlayer"){
		state->onePlayer();
	} else if (cmd == "twoPlayer"){
		state->twoPlayer();
	} else if (cmd == "fire"){
		state->fire();
	} else if (cmd == "back"){
		state->back();
	}
}

void GameThreadFunctor::run()
{
	this->takeCommand();
}
#include <iostream>
#include <string>
#include "threadFunctors/GameThreadFunctor.hpp"

/*////////////////////////////////////////////////////////////
////////////   			Public Methods			//////////////
*/////////////////////////////////////////////////////////////

GameThreadFunctor::GameThreadFunctor(	osapi::MsgQueue* gameMq,
										osapi::MsgQueue* commMq, 
										osapi::MsgQueue* printMq)
{
	gameMq_ = gameMq;
	commMq_ = commMq;
	printMq_ = printMq;
	state = new Idle(this);
}

void GameThreadFunctor::setCurrent(State* s){
	state = s;
}

osapi::MsgQueue* GameThreadFunctor::getGameMq(){
	return gameMq_;
}

osapi::MsgQueue* GameThreadFunctor::getCommMq(){
	return commMq_;
}

osapi::MsgQueue* GameThreadFunctor::getPrintMq(){
	return printMq_;
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

/*////////////////////////////////////////////////////////////
////////////   		  Protected Methods			//////////////
*/////////////////////////////////////////////////////////////

void GameThreadFunctor::run()
{
	std::cout << "GameThreadFunctor::run()" << std::endl;

	while(!(isPrintThreadReady_ && isCommThreadReady_)){
		unsigned long id;
		osapi::Message* msg = gameMq_->receive(id);
		readyHandler(id, msg);
		delete(msg);
	}

	std::cout << "GameThreadFunctor: PrintThread and CommThread ready" << std::endl;
	for(;;){
		unsigned long id;
		osapi::Message* msg = gameMq_->receive(id);
		msgHandler(id, msg);
		delete(msg);
	}
}


/*////////////////////////////////////////////////////////////
////////////   		  Private Methods			//////////////
*/////////////////////////////////////////////////////////////

void GameThreadFunctor::readyHandler(int id, osapi::Message* msg){
	switch(id){
		case ID_PRINT_READY_IND:
		{
			std::cout << "Print Thread returned ready" << std::endl;
			isPrintThreadReady_ = true;
		} break;
		case ID_COMM_READY_IND:
		{
			std::cout << "Comm Thread returned ready" << std::endl;
			isCommThreadReady_ = true;
		} break;
		default:
		{

		} break;
	}
}

void GameThreadFunctor::msgHandler(int id, osapi::Message* msg){
	switch(id){
		case ID_COMM_I2C_HIT_CFM:
		{
			handleIdCommI2CHitCfm(static_cast<CommI2CHitCfm*>(msg));
		} break;
		case ID_COMM_UART_COMMAND_IND:
		{
			handleIdCommUARTCommandInd(static_cast<CommUARTCommandInd*>(msg));
		} break;
		default:
		{

		} break;
	}
}

void GameThreadFunctor::handleIdCommI2CHitCfm(CommI2CHitCfm* msg){
	state->hit(msg->fieldHit);
}

void GameThreadFunctor::handleIdCommUARTCommandInd(CommUARTCommandInd* msg){
	acceptCommand(msg->command);
}

void GameThreadFunctor::acceptCommand(char command){
	switch(command){
		case 'u':
		{
			state->up();
		} break;
		case 'd':
		{
			state->down();
		} break;
		case 'l':
		{	
			state->left();
		} break;
		case 'r':
		{
			state->right();
		} break;
		case '1':
		{
			state->onePlayer();
		} break;
		case '2':
		{
			state->twoPlayer();
		} break;
		case 'f':
		{
			state->fire();
		} break;
		case 'b':
		{
			state->back();
		} break;
		default:
		{

		} break;
	}
}

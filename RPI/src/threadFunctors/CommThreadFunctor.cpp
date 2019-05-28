#include <iostream>
#include <string>
#include <unistd.h>
#include "threadFunctors/CommThreadFunctor.hpp"

/*////////////////////////////////////////////////////////////
////////////   			Public Methods			//////////////
*/////////////////////////////////////////////////////////////

CommThreadFunctor::CommThreadFunctor(	osapi::MsgQueue* commMq,
										osapi::MsgQueue* gameMq)
{
	commMq_ = commMq;
	gameMq_ = gameMq;
}

/*////////////////////////////////////////////////////////////
////////////   			Protected Methods		//////////////
*/////////////////////////////////////////////////////////////

void CommThreadFunctor::run(){
	init();

	for(;;){
		unsigned long id;
		osapi::Message* msg = commMq_->receive(id);
		msgHandler(id, msg);
		delete(msg);
	}
}

/*////////////////////////////////////////////////////////////
////////////   			Private Methods			//////////////
*/////////////////////////////////////////////////////////////

void CommThreadFunctor::init(){
	//Initialize UART and I2C here

	CommReadyInd* msg = new CommReadyInd();
	gameMq_->send(ID_COMM_READY_IND, msg);
}

void CommThreadFunctor::msgHandler(int id, osapi::Message* msg){
	switch(id){
		case ID_GAME_UART_COMMAND_IND:
		{
			handleIdGameUARTCommandInd(static_cast<GameUARTCommandInd*>(msg));
		} break;
		case ID_GAME_I2C_SEND_MAP_IND:
		{
			handleIdGameI2CSendMapInd(static_cast<GameI2CSendMapInd*>(msg));
		} break;
		case ID_GAME_I2C_GET_HIT_REQ:
		{
			handleIdGameI2CGetHitReq(static_cast<GameI2CGetHitReq*>(msg));
		} break;
		case ID_TEST_UART_COMMAND_IND:
		{
			handleIdTestUARTCommandInd(static_cast<TestUARTCommandInd*>(msg));
		}
		default:
		{

		} break;
	}
}

void CommThreadFunctor::handleIdGameUARTCommandInd(GameUARTCommandInd* msg){
	//Send command in message over UART to PSoC_spiller
	std::cout << "CommThreadFunctor sends " << msg->command << " over UART" << std::endl;
}

void CommThreadFunctor::handleIdGameI2CSendMapInd(GameI2CSendMapInd* msg){
	//Send Map over I2C to PSoC_felt
	std::cout << "CommThreadFunctor sends " << msg->map << " over I2C" << std::endl;
}

void CommThreadFunctor::handleIdGameI2CGetHitReq(GameI2CGetHitReq* msg){
	//for now just send some random field back, with 50% miss rate 
	std::cout << "CommThreadFunctor sends hitReq over I2C" << std::endl;
	srand(time(nullptr));
	int fieldHit = rand() % 9;
	if (fieldHit > 9) fieldHit = 0;
	std::cout << "I2C returns field hit: " << fieldHit << std::endl;
	sendI2CHitCfm(fieldHit);
	//Get field hit over I2C and return ID_COMM_I2C_HIT to gameMq_ containing the hit field 
}

void CommThreadFunctor::handleIdTestUARTCommandInd(TestUARTCommandInd* msg){
	sendUARTCommandInd(msg->command);
}

void CommThreadFunctor::sendUARTCommandInd(char command){
	CommUARTCommandInd* commandMsg = new CommUARTCommandInd();
	commandMsg->command = command;
	gameMq_->send(ID_COMM_UART_COMMAND_IND, commandMsg);
}

void CommThreadFunctor::sendI2CHitCfm(int fieldHit){
	CommI2CHitCfm* hitMsg = new CommI2CHitCfm();
	hitMsg->fieldHit = fieldHit;
	gameMq_->send(ID_COMM_I2C_HIT_CFM, hitMsg);
}
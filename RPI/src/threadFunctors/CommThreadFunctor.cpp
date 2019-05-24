#include <iostream>
#include <string>
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
	std::cout << "CommThreadFunctor::init()" << std::endl;

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
		default:
		{

		} break;
	}
}

void CommThreadFunctor::handleIdGameUARTCommandInd(GameUARTCommandInd* msg){
	//Send command in message over UART to PSoC_spiller
}

void CommThreadFunctor::handleIdGameI2CSendMapInd(GameI2CSendMapInd* msg){
	//Send Map over I2C to PSoC_felt
}

void CommThreadFunctor::handleIdGameI2CGetHitReq(GameI2CGetHitReq* msg){
	//Get field hit over I2C and return ID_COMM_I2C_HIT to gameMq_ containing the hit field 
}
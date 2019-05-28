#include <iostream>
#include <string>
#include <unistd.h>
#include "threadFunctors/TestThreadFunctor.hpp"
#include <osapi/Utility.hpp>
/*////////////////////////////////////////////////////////////
////////////   			Public Methods			//////////////
*/////////////////////////////////////////////////////////////

TestThreadFunctor::TestThreadFunctor(	osapi::MsgQueue* commMq)
{
	commMq_ = commMq;
}

/*////////////////////////////////////////////////////////////
////////////   			Protected Methods		//////////////
*/////////////////////////////////////////////////////////////

void TestThreadFunctor::run(){

	for (;;){
		char command;
		std::cin >> command;
		sendUARTCommandInd(command);
	}
}

void TestThreadFunctor::sendUARTCommandInd(char command){
	TestUARTCommandInd* commandMsg = new TestUARTCommandInd();
	commandMsg->command = command;
	commMq_->send(ID_TEST_UART_COMMAND_IND, commandMsg);
}
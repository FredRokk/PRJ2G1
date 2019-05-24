#include <iostream>
#include <unistd.h>
#include <osapi/MsgQueue.hpp>
#include <osapi/Thread.hpp>

#include "threadFunctors/GameThreadFunctor.hpp"
#include "threadFunctors/CommThreadFunctor.hpp"
#include "threadFunctors/GUIThreadFunctor.hpp"

int main(){
	osapi::MsgQueue gameMq(10);
	osapi::MsgQueue commMq(10);
	osapi::MsgQueue printMq(10);

	GameThreadFunctor gameTF(&gameMq, &commMq, &printMq);
	CommThreadFunctor commTF(&commMq, &gameMq);
	GUIThreadFunctor GUITF(&printMq, &gameMq);

	osapi::Thread gameThread(&gameTF);
	osapi::Thread commThread(&commTF);
	osapi::Thread GUIThread(&	GUITF);

	gameThread.start();
	commThread.start();
	GUIThread.start();

	gameThread.join();
	commThread.join();
	GUIThread.join();
}
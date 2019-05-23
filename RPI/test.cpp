#include <iostream>
#include <unistd.h>
#include <osapi::MessageQueue.hpp>
#include <osapi::Thread.hpp>

#include "threadFunctors/GameThreadFunctor.hpp"
#include "threadFunctors/CommThreadFunctor.hpp"
#include "threadFunctors/GUIThreadFunctor.hpp"

int main(){
	osapi::MessageQueue gameMq(10);
	osapi::MessageQueue commMq(10);
	osapi::MessageQueue printMq(10);

	GameThreadFunctor gameTF(&gameMq, &commMq, &printMq);
	CommThreadFunctor commTF(&commMq, &gameMq);
	GUIThreadFunctor GUITF(&printMq, $gameMq);

	Thread gameThread(gameTF);
	Thread commThread(commTF);
	Thread GUIThread(GUITF);

	gameThread.start();
	commThread.start();
	GUIThread.start();

	gameThread.join();
	commThread.join();
	GUIThread.join();
}
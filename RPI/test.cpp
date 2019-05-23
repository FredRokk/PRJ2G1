#include <iostream>
#include <unistd.h>
#include "threadFunctors/GameThreadFunctor.hpp"

int main(){
	GameThreadFunctor gameTF;

	for(;;){
		gameTF.takeCommand();
	}
}
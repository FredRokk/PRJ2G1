#include <iostream>
#include <unistd.h>
#include "GameThreadFunctor.hpp"

int main(){
	GameThreadFunctor gameTF;

	for(;;){
		gameTF.takeCommand();
	}
}
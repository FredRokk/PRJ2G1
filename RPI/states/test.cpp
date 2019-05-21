#include <iostream>
#include <unistd.h>
#include "GameThreadFunctor.hpp"

using namespace std;

int main(){
	GameThreadFunctor gameTF;

	for(;;){
		gameTF.takeCommand();
	}
}
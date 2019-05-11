#include <iostream>
#include <unistd.h>
#include "Classes.hpp"

using namespace std;

int main(){
	Machine m;

	for(;;){
		sleep(2);
		m.next();
	}
}
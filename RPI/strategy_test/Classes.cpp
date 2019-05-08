using namespace std;
#include "Classes.hpp"
#include <iostream>
#include <unistd.h>

Machine::Machine(){
	state = new First(this);
}

void Machine::setCurrent(State* s){
	state = s;
}

void Machine::next(){
	state->next();
}

void Machine::singlePlayer(){
	state->singlePlayer();
}

void Machine::multiPlayer(){
	state->multiPlayer();
}


void State::next(){
	cout << "Default next called" << endl;
}

First::First(Machine* m){
	this->m = m;
	cout << "First state ctor" << endl;
}

First::~First(){
	cout << "First dtor" << endl;
}

void First::next(){
	cout << "Going from First to Second" << endl;
	m->setCurrent(new Second(m));
	delete this;
}

Second::Second(Machine* m){
	this->m = m;
	cout << "Second ctor" << endl;
}

Second::~Second(){
	cout << "Second dtor" << endl;
}

void Second::next(){
	cout << "Going from Second to Third" << endl;
	m->setCurrent(new Third(m));
	delete this;
}

Third::Third(Machine* m){
	this->m = m;
	cout << "Third ctor" << endl;
}

Third::~Third(){
	cout << "Third dtor" << endl;
}
void Third::next(){
	cout << "Goinf from Third to First" << endl;
	m->setCurrent(new First(m));
	delete this;
}
#ifndef PRACTICE
#define PRACTICE

#include "State.hpp"
#include "Idle.hpp"
#include "GameThreadFunctor.hpp"

class Practice: public State
{
public:
	Practice(GameThreadFunctor* gameTF, int selectedMap);
	~Practice();
	void fire();
	void hit(int field);

private:
	int selectedMap_;
	//Map map
};

#endif
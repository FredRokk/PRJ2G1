#ifndef GAME_THREAD_FUNCTOR
#define GAME_THREAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>

#include "states/State.hpp"
#include "states/Idle.hpp"

class GameThreadFunctor: public osapi::ThreadFunctor
{
private:
	class State* state;
public: 
	GameThreadFunctor();
	void takeCommand();
	void setCurrent(State* s);
protected:
	virtual void run();
};

#endif
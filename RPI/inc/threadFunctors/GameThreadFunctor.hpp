#ifndef GAME_THREAD_FUNCTOR
#define GAME_THREAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MessageQueue.hpp>

#include "states/State.hpp"
#include "states/Idle.hpp"

class GameThreadFunctor: public osapi::ThreadFunctor
{
private:
	class State* state;
	osapi::MessageQueue* gameMq_;
	osapi::MessageQueue* commMq_;
	osapi::MessageQueue* printMq_;
	bool isPrintThreadReady_ = false;
	bool isCommThreadReady_ = false;
public: 
	GameThreadFunctor(	osapi::MessageQueue* gameMq_,
						osapi::MessageQueue* commMq, 
						osapi::MessageQueue* printMq);
	void takeCommand();
	void setCurrent(State* s);
protected:
	virtual void run();
};

#endif
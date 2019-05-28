#ifndef GAME_THREAD_FUNCTOR
#define GAME_THREAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>

#include "communication/Messages.hpp"
#include "states/State.hpp"
#include "states/Idle.hpp"

class GameThreadFunctor: public osapi::ThreadFunctor
{
public: 
	GameThreadFunctor(	osapi::MsgQueue* gameMq,
						osapi::MsgQueue* commMq, 
						osapi::MsgQueue* printMq);
	void setCurrent(State* s);
	osapi::MsgQueue* getGameMq();
	osapi::MsgQueue* getCommMq();
	osapi::MsgQueue* getPrintMq();
protected:
	virtual void run();
private:
	class State* state;
	osapi::MsgQueue* gameMq_;
	osapi::MsgQueue* commMq_;
	osapi::MsgQueue* printMq_;
	bool isPrintThreadReady_ = false;
	bool isCommThreadReady_ = false;

	void readyHandler(int id, osapi::Message* msg);
	void msgHandler(int id, osapi::Message* msg);
	void handleIdCommUARTCommandInd(CommUARTCommandInd* msg);
	void handleIdCommI2CHitCfm(CommI2CHitCfm* msg);
	void acceptCommand(char command);
};

#endif
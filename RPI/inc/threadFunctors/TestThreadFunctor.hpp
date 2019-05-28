#ifndef TEST_THREAD_FUNCTOR
#define TEST_THERAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>

#include "communication/Messages.hpp"


class TestThreadFunctor: public osapi::ThreadFunctor
{
public: 
	TestThreadFunctor(osapi::MsgQueue* commMq);
protected:
	virtual void run();
private:
	osapi::MsgQueue* commMq_;
	
	void sendUARTCommandInd(char command);
};

#endif
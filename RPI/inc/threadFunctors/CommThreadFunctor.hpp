#ifndef COMM_THREAD_FUNCTOR
#define COMM_THREAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MessageQueue.hpp>


class CommThreadFunctor: public osapi::ThreadFunctor
{
private:
	osapi::MessageQueue* commMq_;
	osapi::MessageQueue* gameMq_;
public: 
	GameThreadFunctor(osapi::MessageQueue* commMq, osapi::MessageQueue* gameMq_);
protected:
	virtual void run();
};

#endif
#ifndef PRINT_THREAD_FUNCTOR
#define PRINT_THREAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MessageQueue.hpp>

class PrintThreadFunctor: public osapi::ThreadFunctor
{
private:
	osapi::MessageQueue* printMq_;
	osapi::MessageQueue* gameMq_;
public: 
	PrintThreadFunctor(osapi::MessageQueue* printMq, osapi::MessageQueue* gameMq_);
protected:
	virtual void run();
};

#endif
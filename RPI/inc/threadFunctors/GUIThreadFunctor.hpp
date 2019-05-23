#ifndef GUI_THREAD_FUNCTOR
#define GUI_THREAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MessageQueue.hpp>

#include "threadFunctors/PrintThreadFunctor"

class GUIThreadFunctor: public osapi::ThreadFunctor
{
private:
	osapi::MessageQueue* printMq_;
	osapi::MessageQueue* gameMq_;

	void spawnPrintThread();
public: 
	GUIThreadFunctor(osapi::MessageQueue* printMq, osapi::MessageQueue* gameMq);
protected:
	virtual void run();
};

#endif
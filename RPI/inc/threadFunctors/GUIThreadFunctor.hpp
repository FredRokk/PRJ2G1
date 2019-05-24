#ifndef GUI_THREAD_FUNCTOR
#define GUI_THREAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>

#include "communication/Messages.hpp"
#include "threadFunctors/PrintThreadFunctor.hpp"

class GUIThreadFunctor: public osapi::ThreadFunctor
{
public: 
	GUIThreadFunctor(osapi::MsgQueue* printMq, osapi::MsgQueue* gameMq);
protected:
	virtual void run();
private:
	osapi::MsgQueue* printMq_;
	osapi::MsgQueue* gameMq_;

	void init();
};

#endif
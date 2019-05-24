#ifndef PRINT_THREAD_FUNCTOR
#define PRINT_THREAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>

#include "communication/Messages.hpp"

class PrintThreadFunctor: public osapi::ThreadFunctor
{
public: 
	PrintThreadFunctor(osapi::MsgQueue* printMq, osapi::MsgQueue* gameMq_);
protected:
	virtual void run();
private:
	osapi::MsgQueue* printMq_;
	osapi::MsgQueue* gameMq_;

	void init();
	void msgHandler(int id, osapi::Message* msg);
	void handleIdGameShowMenuInd(GameShowMenuInd* msg);
	void handleIdGameCleanMenuInd(GameCleanMenuInd* msg);
	void handleIdGameUpdatePointsInd(GameUpdatePointsInd* msg);
	void handleIdGameUpdateShotsInd(GameUpdateShotsInd* msg);
	void handleIdGameSetNextPlayerInd(GameSetNextPlayerInd* msg);
	void handleIdGameHighscoreChangeChar(GameHighscoreChangeChar* msg);

};

#endif
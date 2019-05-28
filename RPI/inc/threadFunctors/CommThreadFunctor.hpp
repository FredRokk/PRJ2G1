#ifndef COMM_THREAD_FUNCTOR
#define COMM_THREAD_FUNCTOR

#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>

#include "communication/Messages.hpp"


class CommThreadFunctor: public osapi::ThreadFunctor
{
public: 
	CommThreadFunctor(osapi::MsgQueue* commMq, osapi::MsgQueue* gameMq_);
protected:
	virtual void run();
private:
	osapi::MsgQueue* commMq_;
	osapi::MsgQueue* gameMq_;

	void init();
	void msgHandler(int id, osapi::Message* msg);
	void handleIdGameUARTCommandInd(GameUARTCommandInd* msg);
	void handleIdGameI2CSendMapInd(GameI2CSendMapInd* msg);
	void handleIdGameI2CGetHitReq(GameI2CGetHitReq* msg);
	void handleIdTestUARTCommandInd(TestUARTCommandInd* msg);

	void sendUARTCommandInd(char command);
	void sendI2CHitCfm(int fieldHit);
};

#endif
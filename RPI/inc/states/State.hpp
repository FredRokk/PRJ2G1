#ifndef STATE
#define STATE

#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>
#include "communication/Messages.hpp"

class State
{
public:
	virtual ~State();
	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();
	virtual void onePlayer();
	virtual void twoPlayer();
	virtual void back();
	virtual void fire();
	virtual void hit(int field);
	void miss();

protected:
	class GameThreadFunctor* gameTF;
	bool returning_ = false;
	std::string menuName_;

	void sendShowMsg(osapi::MsgQueue* mq, std::string menu);
	void sendCleanMsg(osapi::MsgQueue* mq, std::string menu);
	void sendMapMsg(osapi::MsgQueue* mq, std::string map);
	void sendHitRequest(osapi::MsgQueue* mq);
};

#endif
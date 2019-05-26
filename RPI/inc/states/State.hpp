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

	void sendUARTCommandInd(osapi::MsgQueue* mq, char command);
	void sendMapInd(osapi::MsgQueue* mq, std::string map);
	void sendHitReq(osapi::MsgQueue* mq);
	void sendShowInd(osapi::MsgQueue* mq, std::string menu);
	void sendCleanInd(osapi::MsgQueue* mq, std::string menu);
	void sendChangeMapInd(osapi::MsgQueue* mq, int map);
	void sendPointsInd(osapi::MsgQueue* mq, int player, int points);
	void sendShotsInd(osapi::MsgQueue* mq, int player, int shots);
	void sendNextPlayerInd(osapi::MsgQueue* mq, int player);
	void sendArmedInd(osapi::MsgQueue* mq, bool armed, std::string menu);
	void sendMissInd(osapi::MsgQueue* mq, std::string menu);
	void sendHighscoreChangeCharInd(osapi::MsgQueue*, int player, int charNum, char newChar);

};

#endif
#include <iostream>

#include "states/State.hpp"

/* 
class: State
Implementation of the State interface's member functions
*/

State::~State(){
	std::cout << "Default: dtor" << std::endl;
}

void State::up(){
	std::cout << "Default: up" << std::endl;
}

void State::down(){
	std::cout << "Default: down" << std::endl;
}
void State::left(){
	std::cout << "Default: left" << std::endl;
}
void State::right(){
	std::cout << "Default: right" << std::endl;
}
void State::onePlayer(){
	std::cout << "Default: onePlayer" << std::endl;
}
void State::twoPlayer(){
	std::cout << "Default: twoPlayer" << std::endl;
}
void State::back(){
	std::cout << "Default: back" << std::endl;
	if(returning_){
		std::cout << "MapSelect: return - returning is true, setting returning to false" << std::endl;
		returning_ = false;
	} else {
		std::cout << "Mapselect: return - setting return to true" << std::endl;
		returning_ = true;
	}
}
void State::fire(){
	std::cout << "Default: fire" << std::endl;
}
void State::hit(int field){
	std::cout << "Default: hit" << std::endl;
}

void State::miss(){
	std::cout << "Default: miss" << std::endl;
}

void State::sendUARTCommandInd(osapi::MsgQueue* mq, char command){
	GameUARTCommandInd* commandMsg = new GameUARTCommandInd();
	commandMsg->command = command;
	mq->send(ID_GAME_UART_COMMAND_IND, commandMsg);
}

void State::sendMapInd(osapi::MsgQueue* mq, std::string map){
	GameI2CSendMapInd* mapMsg = new GameI2CSendMapInd();
	mapMsg->map = map;
	mq->send(ID_GAME_I2C_SEND_MAP_IND, mapMsg);
}

void State::sendHitReq(osapi::MsgQueue* mq){
	GameI2CGetHitReq* hitMsg = new GameI2CGetHitReq();
	mq->send(ID_GAME_I2C_GET_HIT_REQ, hitMsg);
}

void State::sendShowInd(osapi::MsgQueue* mq, std::string menu){
	GameShowMenuInd* showMsg = new GameShowMenuInd();
	showMsg->menu = menu;
	mq->send(ID_GAME_SHOW_MENU_IND, showMsg);
}

void State::sendCleanInd(osapi::MsgQueue* mq, std::string menu){
	GameCleanMenuInd* cleanMsg = new GameCleanMenuInd();
	cleanMsg->menu = menu;
	mq->send(ID_GAME_CLEAN_MENU_IND, cleanMsg);
}

void State::sendChangeMapInd(osapi::MsgQueue* mq, int map){
	GameChangeMapInd* changeMapMsg = new GameChangeMapInd();
	changeMapMsg->map = map;
	mq->send(ID_GAME_CHANGE_MAP_IND, changeMapMsg);
}

void State::sendPointsInd(osapi::MsgQueue* mq, int player, int points){
	GameUpdatePointsInd* pointsMsg = new GameUpdatePointsInd();
	pointsMsg->player = player;
	pointsMsg->points = points;
	mq->send(ID_GAME_UPDATE_POINTS_IND, pointsMsg);
}

void State::sendShotsInd(osapi::MsgQueue* mq, int player, int shots){
	GameUpdateShotsInd* shotsMsg = new GameUpdateShotsInd();
	shotsMsg->player = player;
	shotsMsg->shots = shots;
	mq->send(ID_GAME_UPDATE_SHOTS_IND, shotsMsg);
}

void State::sendNextPlayerInd(osapi::MsgQueue* mq, int player){
	GameSetNextPlayerInd* nextPlayerMsg = new GameSetNextPlayerInd();
	nextPlayerMsg->player = player;
	mq->send(ID_GAME_SET_NEXT_PLAYER_IND, nextPlayerMsg);
}

void State::sendArmedInd(osapi::MsgQueue* mq, bool armed, std::string menu){
	GameUpdateCanonArmedInd* armedMsg = new GameUpdateCanonArmedInd();
	armedMsg->armed = armed;
	armedMsg->menu = menu;
	mq->send(ID_GAME_UPDATE_CANON_ARMED_IND, armedMsg);
}

void State::sendMissInd(osapi::MsgQueue* mq, std::string menu){
	GameNotifyMissInd* missMsg = new GameNotifyMissInd();
	missMsg->menu = menu;
	mq->send(ID_GAME_NOTIFY_MISS_IND, missMsg);
}

void State::sendHighscoreChangeCharInd(osapi::MsgQueue* mq, int player, int charNum, char newChar){
	GameHighscoreChangeChar* changeCharMsg = new GameHighscoreChangeChar();
	changeCharMsg->player = player;
	changeCharMsg->charNum = charNum;
	changeCharMsg->newChar = newChar;
	mq->send(ID_GAME_HIGHSCORE_CHANGE_CHAR_IND, changeCharMsg);
}
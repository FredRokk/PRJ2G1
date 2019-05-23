#ifndef MESSAGES
#define MESSAGES

#include <string>
#include <osapi/Message.hpp>

enum {
	ID_PRINT_READY_IND,
	ID_COMM_READY_IND,
	ID_COMM_I2C_HIT_CFM,
	ID_COMM_UART_COMMAND_IND,
	ID_GAME_UART_COMMAND_IND,
	ID_GAME_I2C_SEND_MAP_IND,
	ID_GAME_I2C_GET_HIT_REQ,
	ID_GAME_SHOW_MENU_IND,
	ID_GAME_CLEAN_MENU_IND,
	ID_GAME_UPDATE_POINTS_IND,
	ID_GAME_UPDATE_SHOTS_IND,
	ID_GAME_SET_NEXT_PLAYER_IND,
	ID_GAME_HIGHSCORE_CHANGE_CHAR_IND,
};

/*////////////////////////////////////////////////////////////
////////////   Messages originating from Print	//////////////
*/////////////////////////////////////////////////////////////

//PrintThread to GameThread when PrintThread is initialized
struct PrintReadyInd: public osapi::Message
{
	
};

/*////////////////////////////////////////////////////////////
////////////   Messages originating from Comm	//////////////
*/////////////////////////////////////////////////////////////

//CommThread to GameThread when CommThread is initialized
struct CommReadyInd: public osapi::Message
{
	
};

//CommThread to GameThread when UART char is received
struct CommUARTCommandInd: public osapi::Message
{
	char command;
};

//CommThread to GameThread when CommThread has evaluated what field is hit
struct CommI2CHitCfm: public osapi::Message
{
	int fieldHit;
};

/*////////////////////////////////////////////////////////////
////////////   Messages originating from Game	//////////////
*/////////////////////////////////////////////////////////////

//GameThread to CommThread when system wants to send a char over UART (Versus and Practice)
struct GameUARTCommand: public osapi::Message
{
	char command;
};

//GameThread to CommThread when new map should be displayed (Versus and Practice)
struct GameI2CSendMapInd: public osapi::Message
{
	std::string map;
};

//GameThread to CommThread when GameThread requests field hit (Versus and Practice)
struct GameI2CGetHitReq: public osapi::Message
{
	
};

//GameThread to PrintThread when GameThread wishes to show a new menu (All states)
struct GameShowMenuInd: public osapi::Message
{
	std::string menu;
};

//GameThread to PrintThread when GameThread wishes to clean up a menu (All states)
struct GameCleanWindowInd: public osapi::Message
{
	std::string menu;
};

//GameThread to PrintThread when GameThread wishes to update points for a player (Versus state only)
struct GameUpdatePointsInd: public osapi::Message
{
	int player;
	int points;
};

//GameThread to PrintThread when GameThread wishes to update a player's current shots (Versus state only)
struct GameUpdateShotsInd: public osapi::Message
{
	int player;
	int shots;
};

//GameThread to PrintThread when GameThread wishes to update which player is next to shoot (Versus state only)
struct GameSetNextPlayerInd: public osapi::Message
{
	int player;
};

//GameThread to PrintThread when GameThread wishes to update a char in player's name when posting highscore (Both highscore states)
struct GameHighscoreChangeChar: public osapi::Message
{
	int player;
	int charNum;
	char newChar;
};

#endif
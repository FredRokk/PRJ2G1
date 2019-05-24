#include <iostream>
#include <string>
#include "threadFunctors/PrintThreadFunctor.hpp"

/*////////////////////////////////////////////////////////////
////////////   			Public Methods			//////////////
*/////////////////////////////////////////////////////////////

PrintThreadFunctor::PrintThreadFunctor(	osapi::MsgQueue* printMq, 
										osapi::MsgQueue* gameMq)
{
	printMq_ = printMq;
	gameMq_ = gameMq;
}

/*////////////////////////////////////////////////////////////
////////////   			Protected Methods		//////////////
*/////////////////////////////////////////////////////////////

void PrintThreadFunctor::run(){
	init();



	for(;;){
		unsigned long id;
		osapi::Message* msg = printMq_->receive(id);
		msgHandler(id, msg);
		delete(msg);
	}
}

/*////////////////////////////////////////////////////////////
////////////   			Private Methods			//////////////
*/////////////////////////////////////////////////////////////

void PrintThreadFunctor::init(){
	//Initialize printy things here
	std::cout << "PrintThreadFunctor::init()" << std::endl;
	
	//Then send ready message
	PrintReadyInd* msg = new PrintReadyInd();
	gameMq_->send(ID_PRINT_READY_IND, msg);
}


void PrintThreadFunctor::msgHandler(int id, osapi::Message* msg){
	switch(id){
		case ID_GAME_SHOW_MENU_IND:
		{
			handleIdGameShowMenuInd(static_cast<GameShowMenuInd*>(msg));
		} break;
		case ID_GAME_CLEAN_MENU_IND:
		{
			handleIdGameCleanMenuInd(static_cast<GameCleanMenuInd*>(msg));
		} break;
		case ID_GAME_UPDATE_POINTS_IND:
		{
			handleIdGameUpdatePointsInd(static_cast<GameUpdatePointsInd*>(msg));
		} break;
		case ID_GAME_UPDATE_SHOTS_IND:
		{
			handleIdGameUpdateShotsInd(static_cast<GameUpdateShotsInd*>(msg));
		} break;
		case ID_GAME_SET_NEXT_PLAYER_IND:
		{
			handleIdGameSetNextPlayerInd(static_cast<GameSetNextPlayerInd*>(msg));
		} break;
		case ID_GAME_HIGHSCORE_CHANGE_CHAR_IND:
		{
			handleIdGameHighscoreChangeChar(static_cast<GameHighscoreChangeChar*>(msg));
		} break;
		default:
		{

		} break;
	}
}

void PrintThreadFunctor::handleIdGameShowMenuInd(GameShowMenuInd* msg){
	//Get menu string from msg and show the menu corresponding to the string
}
void PrintThreadFunctor::handleIdGameCleanMenuInd(GameCleanMenuInd* msg){
	//Get menu string from msg and clean the menu corresponding to the string
}
void PrintThreadFunctor::handleIdGameUpdatePointsInd(GameUpdatePointsInd* msg){
	//Get player int and points ind and update the points of the player in all point-containing menus
}
void PrintThreadFunctor::handleIdGameUpdateShotsInd(GameUpdateShotsInd* msg){
	//Get player int and shots ind and update the shots of the player in Versus menu
}
void PrintThreadFunctor::handleIdGameSetNextPlayerInd(GameSetNextPlayerInd* msg){
	//Get player int and update the next player to shoot in Versus menu
}
void PrintThreadFunctor::handleIdGameHighscoreChangeChar(GameHighscoreChangeChar* msg){
	//Get player int, charNum int and newChar char and update the charNum to newChar in corresponding player's highscore window
}
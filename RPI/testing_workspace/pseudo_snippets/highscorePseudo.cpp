
#include <stdlib.h>

char name[4] = "AAA";
int currentChar = 0;
int playedMap, playerOneScore, playerTwoScore, scoreToBeat;


PlayerOneHighscore(int playedMap, int playerOneScore, int playerTwoScore, int scoreToBeat){

	this.playedMap = playedMap;
	this.playerOneScore = playerOneScore;
	this.playerTwoScore = playerTwoScore;
	this.scoreToBeat = scoreToBeat;

	Message* msg = new showPlayerOneHighScore();
	guimq->send(SHOW_PLAYER_ONE_HIGHSCORE(), nullptr);
}

virtual void return(){
	if (returning) {
		quimq->send(HIDE_RETURN_MESSAGE(), nullptr);
		returning = false;
	} else {
		Message* msg = new showReturnMessage();
		quimq->send(SHOW_RETURN_MESSAGE(), nullptr);
		returning = true;
	}
}

virtual void fire(){
	if(returning = true){
		exitState();
	}
	if (currentChar < 3){
		currentChar++;
	} else {
		postHighScore();
	}
}

void postHighScore(){
	GameRules::putHighscore(playedMap, playerOneScore, name);

	exitState();
}

void exitState(){
	if(playerTwoScore > scoreToBeat) {
		game->setState(new PlayerTwoScore(playedMap, playerTwoScore));
		delete this;
	} else {
		game->setState(new Idle());
		delete this;
	}
}
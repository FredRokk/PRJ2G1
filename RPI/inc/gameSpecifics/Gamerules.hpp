#ifndef GAMERULES
#define GAMERULES

#include <string>
#include <vector>
#include "gameSpecifics/Map.hpp"

#define NUMBER_OF_VERSUS_SHOTS 8
#define RANDOM_MAP_CONTENTS "0111122233"
#define DEFAULT_MAP_0 "0313111222"
#define DEFAULT_MAP_1 "0131222131"

#define POINT_VALUE_1 30
#define POINT_VALUE_2 50
#define POINT_VALUE_3 70

//Modifying the definitions below require appropriate changes in private members of Gamerules
#define NUMBER_OF_DEFAULT_MAPS 2
#define NUMBER_OF_DIFFERENT_FIELDS 4

class Gamerules
{
public:
	static int getPoints(Map map, unsigned int field);
	static Map generateMap(unsigned int mapNumber);

	//NYI void postHighScore(int playedMap, int points, std::string name);

private:
	static Map generateRandomMap();
	Gamerules(){};

};

#endif
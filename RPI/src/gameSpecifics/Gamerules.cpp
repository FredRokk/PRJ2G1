#include "gameSpecifics/Gamerules.hpp"
#include <time.h>
#include <cstdlib>
#include <algorithm>

int Gamerules::getPoints(Map map, unsigned int field){
	int fieldValue = map.getField(field);
	int retValue = 0;
	switch(fieldValue){
		case 1:
		{
			retValue = POINT_VALUE_1;
		} break;
		case 2:
		{
			retValue = POINT_VALUE_2;
		} break;
		case 3:
		{
			retValue = POINT_VALUE_3;
		} break;
		default:
		{

		}
	}
	return retValue;
}

Map Gamerules::generateMap(unsigned int mapNumber)
{
	if (mapNumber < NUMBER_OF_DEFAULT_MAPS)
	{
		if (mapNumber == 0) return Map(DEFAULT_MAP_0);
		if (mapNumber == 1) return Map(DEFAULT_MAP_1);
	}
	return generateRandomMap();
}

Map Gamerules::generateRandomMap(){
	std::srand(time(0));
	std::string randomMapContent = RANDOM_MAP_CONTENTS;
	std::random_shuffle(randomMapContent.begin()+1, randomMapContent.end());
	return Map(randomMapContent);
}
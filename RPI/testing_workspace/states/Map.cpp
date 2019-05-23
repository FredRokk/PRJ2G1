#include "Gamerules.hpp"
#include "Map.hpp"

#include <iostream>

std::string Map::getMapString(){
	return map_;
}


int Map::getField(unsigned int field){
	if(map_.length() > field){
		return map_.at(field)-'0'; // .at operator conversion - '1' - '0' in char is 49-48 in int.
	}
	return 0;
}

void Map::setField(unsigned int field, unsigned int value){
	if(map_.length() > field){
		if (value < NUMBER_OF_DIFFERENT_FIELDS){
			map_.at(field) = value+'0'; // .at operator conversion - 1 + '0' in char is 1 + 48, which is '1' in char
		} else {
			map_.at(field) = NUMBER_OF_DIFFERENT_FIELDS - 1;
		}
	}
}


void Map::disableField(int field){
	this->setField(field, 0);
}
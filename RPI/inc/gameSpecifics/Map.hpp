#ifndef MAP
#define MAP

#include <string>

class Map
{
public:
	Map();
	Map(const std::string & map): map_(map) {};
	std::string getMapString();
	int getField(unsigned int field);
	void setField(unsigned int field, unsigned int value);
	void disableField(int field);
private:
	std::string map_;
};

#endif


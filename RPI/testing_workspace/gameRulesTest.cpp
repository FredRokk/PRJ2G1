#include <iostream>

#include "Gamerules.hpp"
#include "Map.hpp"

using namespace std;

int main (){
	Map map = Gamerules::generateMap(2);

	cout << "Generated map: " << map.getMapString() << endl << endl;

	unsigned int input;
	for(;;)
	{
		cout << "Enter field to hit: ";
		cin >> input;
		cout << endl;
		cout << "Field hit:" << map.getField(input) << endl;
		cout << "Points awarded:" << Gamerules::getPoints(map, input) << endl;
		cout << "Disabling field" << endl;
		map.disableField(input);
		cout << "Map is now: " << map.getMapString() << endl << endl;
	}
}
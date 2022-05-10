#include "MyMap.h"
#include <iostream>

using namespace std;

void read(string& statement, int& languagePower, MyMap<char, int>& currentMap)
{	
	char buff;

	while (cin.get(buff))
	{
		if (buff == '\n')
		{
			break;
		}

		statement += buff;

		if (currentMap.isInMap(buff)) 
		{
			currentMap.find(buff)->value++;
		}
		else
		{
			currentMap.insert(buff, 1);
			languagePower++;
		}
	}

}


int main()
{
	MyMap<char, int> currentMap;
	
	int languagePower = 0;
	
	string statement = "";

	cout << "Enter the statement: " << endl;;

	read(statement, languagePower, currentMap);

	Coding newEncoding(currentMap, languagePower, statement);
	
	newEncoding.encodingTheStatement(0, languagePower - 1);
	
	newEncoding.printResults();


	

}
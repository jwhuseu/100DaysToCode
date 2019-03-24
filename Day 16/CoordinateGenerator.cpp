/* This program is to create a random outfile
 * that will have the number of generated coordinates 
 * with each x and y coordinates randomly generated.
 */
#include <iostream>
#include <fstream>
#include <cstdlib> 

using namespace std;

int main()
{
	//The number of random coordinates that will be outputted.
	int NumberOfCoordinates = 50; 
	int Length = 6;
	int Height = 6;
	int XCoordinate, YCoordinate;
	
	//Basic outfile generation call and output.
	ofstream OutFile;
	OutFile.open("Output.txt");
	OutFile << NumberOfCoordinates << "\n";
	
	//This section of code will output two random coordinates for x and y.

	for (int n = 0; n < NumberOfCoordinates; n++)
	{
		XCoordinate = rand() % Length;
		YCoordinate = rand() % Height;
		
		OutFile << XCoordinate << " " << YCoordinate << "\n";
	}
	
	OutFile.close();
	
	return 0;
}
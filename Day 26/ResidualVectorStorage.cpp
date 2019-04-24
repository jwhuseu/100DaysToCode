/* This program is designed to test basic 
 * array storage for a multi-equation system
 * and then output the results to terminal.
 */
 
#include <iostream>
using namespace std;

int main()
{	
	//Basic declaration variables
	int EquationCount = 3;
	int VariableNumbers = 50;
	int ArraySize = EquationCount * VariableNumbers;
	
	//Array declaration 
	int ResidualVector[ArraySize] = {};
	
	for (int n = 0; n < VariableNumbers; n++)
	{
		ResidualVector[EquationCount * n] = 0;
		ResidualVector[EquationCount * n + 1] = 1;
		ResidualVector[EquationCount * n + 2] = 2;
	}
	
	//Array output
	for (int n = 0; n < ArraySize; n++)
	{
		cout << ResidualVector[n] << "\n";
	}
	
	return 0;
}
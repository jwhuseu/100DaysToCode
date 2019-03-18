/* This is a basic program to compare mathematical linear algebra operations 
 * against the traditional algorithms used to solve the nonlinear
 * Burgers' equation.
 */
 
 
#include <iostream>
using namespace std;


int main()
{
	//Physical setup and basic discretization schemes
	double Length = 10.0;
	double TotalTime = 10.0;
	int NodeX = 50;
	int TimeStep = 3000;
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeStep;
	
	//Boundary Conditions
	double VelocityLeft = 1.0;
	double VelocityRight = 0.0;
	
	//Initial Conditions
	double LeftShock = 1.0;
	double RightShock = 0.0;
	
	//Array declaration
	double UArray[NodeX] = {};
	double UArrayCopy[NodeX] = {};
	
	//Array fill for calculation purposes 
	
	for (int n = 0; n < NodeX; n++)
	{
		if (n < 0.5 * NodeX)
		{
			UArray[n] = LeftShock;
			UArrayCopy[n] = LeftShock;
		}
		
		if (n >= 0.5 * NodeX)
		{
			UArray[n] = RightShock;
			UArrayCopy[n] = RightShock;
		}
	}
	
	
	//Solver step
	
	for (int Time = 0; Time < 1; Time++)
	{
		for (int n = 1; n < NodeX - 1; n++)
		{
			UArrayCopy[n] = UArray[n] - DeltaTime * UArray[n] / DeltaX * (UArray[n+1] - UArray[n-1]);
		}
		
		//Copy stage
		for (int n = 0; n < NodeX - 1; n++)
		{
			UArray[n] = UArrayCopy[n];
		}
	}
	
	//Output stage
	
	for (int n = 0; n < NodeX; n++)
	{
		cout << UArray[n] << "\n";
	}
	
	return 0;
}
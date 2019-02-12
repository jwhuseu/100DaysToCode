//This is a basic example of explicit for the convection equation
//This solves time with forward Euler and space is solved by using central
//difference in space. 

#include <iostream>
using namespace std;

int main()
{
	double Length = 1.0;
	int xNodes = 25;
	double Time = 5.0;
	int TimeSteps = 50;
	double CFL = 0.5;
	double ConvectionCoefficient = 1.0;
	double BoundaryConditionLeft = 1.0; 
	double BoundaryConditionRight = 1.0; 
	
	double deltaX = Length / (xNodes - 1);
	double deltaTime = CFL * deltaX / ConvectionCoefficient;
	
	
	//Practically "Mesh Generation" step
	double FlowField[xNodes] = {};
	double FlowFieldCopy[xNodes] = {};
	
	//This will initialize the arrays
	//Remember the order of the checks for the boolean operation.
	//Also, is there a way to use only if statements instead of else?
	//Check out the boolean operations for C++.
	
	for (int n = 0; n < xNodes; n++)
	{
		if (n >= 0.25 * xNodes && n <= 0.5 * xNodes)
		{
			FlowField[n] = 2;
			FlowFieldCopy[n] = 2;
		}
		else 
		{
			FlowField[n] = 1;
			FlowFieldCopy[n] = 1;
		}
	}
	
	//Flow Solver Step
	
	for (int Time = 0; Time < TimeSteps; Time++)
	{
		for (int n = 1; n < xNodes - 1; n++)
		{
			/* n starting at 1 and ending at xNodes - 2 is to enforce the 
			boundary condiions. There are two classifications for enforcement
			of boundary conditions. I would call this strongly enforced. While
			not solving a modified equation, the boundary conditions are assumed
			at those points constant without the use of ghost cells or similar. */
			
			FlowFieldCopy[n] = FlowField[n] - ConvectionCoefficient * deltaTime / (2.0 * deltaX) * (FlowField[n+1] - FlowField[n-1]);
		}
		
		//Update the solution field
		for (int n = 0; n < xNodes; n++)
		{
			FlowField[n] = FlowFieldCopy[n];
		}
		
	}
	//Output for arrays
	for (int n = 0; n < xNodes; n++)
	{
		cout << FlowField[n] << endl;
	}
	
	
	return 0;
}
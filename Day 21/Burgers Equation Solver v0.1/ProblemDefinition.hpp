/* This portion of code contains the 
 * problem definition and basic conditions
 * that will be used to construct the 
 * solution.
 */
 
#ifndef PROBLEMDEFINITION
#define PROBLEMDEFINITION

struct ProblemDefinition
{
	//Basic problem definition and discretization
	double Length = 1.0;
	double TotalTime = 0.5;
	int NodeX = 50;
	int TimeStep = 100;
	
	//The delta terms
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TimeStep / TotalTime;
	
	//Initial conditions for basic shock tube type problem
	double LeftShock = 2.0;
	double RightShock = 1.0;
	
	//Initial Conditions for wave like problem
	double InitialPeak = 2.0;
	double InitialLow = 1.0;
	
	//Boundary conditions for initial conditions one
	double LeftBoundaryOne = 2.0;
	double RightBoundaryOne = 1.0;
	
	//Boundary conditions for initial conditions two
	double LeftBoundaryTwo = 1.0;
	double RightBoundaryTwo = 1.0;
};

#endif
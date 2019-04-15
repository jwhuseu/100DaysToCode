/* This code solves the 1D inviscid Burgers'
 * equation using the Lax-Friedrichs method
 * for the flux term.
 */
 
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	//Basic problem statement, dimensions, and discretization
	double Length = 1.0;
	double TotalTime = 0.5;
	int NodeX = 100;
	int TimeStep = 500;
	int UsedTimeStep = 50;
	
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeStep;
	
	//Boundary conditions
	double LeftBoundary = 1.0;
	double RightBoundary = 1.0;
	
	//Initial conditions
	double LowPeak = 1.0;
	double TopPeak = 2.0;
	
	//Array declaration
	double Velocity[NodeX] = {};
	double VelocityCopy[NodeX] = {};
	
	//Array initialization
	for (int n = 0; n < NodeX; n++)
	{
		if (n >= 0.4 * NodeX && n < 0.6 * NodeX)
		{
			Velocity[n] = TopPeak;
			VelocityCopy[n] = TopPeak;
		}
		else 
		{
			Velocity[n] = LowPeak;
			VelocityCopy[n] = LowPeak;
		}
	}
	
	//Solver step 
	for (int TimeCount = 0; TimeCount < UsedTimeStep; TimeCount++)
	{
		for (int n = 1; n < NodeX - 1; n++)
		{
			VelocityCopy[n] = 0.5 * (Velocity[n+1] + Velocity[n-1]) 
								- 0.5 * Velocity[n] * DeltaTime / DeltaX * (Velocity[n+1] - Velocity[n-1]);
		}
	
		//Boundary conditions (really no point to enforce, because they are "Weakly" enforced)
		VelocityCopy[0] = LeftBoundary;
		VelocityCopy[NodeX - 1] = RightBoundary;
	
		//Array update
		for (int n = 0; n < NodeX; n++)
		{
			Velocity[n] = VelocityCopy[n];
		}
	}
	
	//Array output
	for (int n = 0; n < NodeX; n++)
	{
		cout << Velocity[n] << "\n";
	}
	
	return 0;
}
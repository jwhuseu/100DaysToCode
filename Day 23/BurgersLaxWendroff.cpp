/* This code will be solving the inviscid 
 * Burgers' equation using the Lax-Wendroff
 * Scheme.
 */
 
#include <iostream>
using namespace std;

int main()
{
	//Problem discretization and information
	double Length = 1.0;
	double TotalTime = 0.5;
	int NodeX = 250;
	int TimeStep = 500;
	int TimeStepUsed = 50;
	
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeStep;
	
	//Boundary conditions
	double LeftBoundary = 1.0;
	double RightBoundary = 1.0;
	
	//Initial conditions
	double TopPeak = 2.0;
	double BottomPeak = 1.0;
	
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
			Velocity[n] = BottomPeak;
			VelocityCopy[n] = BottomPeak;
		}
	}
	
	//Solver step
	
	for (int TimeCount = 0; TimeCount < TimeStepUsed; TimeCount++)
	{
		//The Jacobian is explicitly declared and will change that once I learn the implementation
		//Boundaries are not changed in the solution solver.
		for (int n = 1; n < NodeX - 1; n++)
		{
			VelocityCopy[n] = Velocity[n] - 0.5 * Velocity[n] * DeltaTime / DeltaX * (Velocity[n+1] - Velocity[n-1])
									  + 0.5 * Velocity[n] * DeltaTime * DeltaTime / DeltaX / DeltaX * 
									  (0.5 * (Velocity[n] + Velocity[n+1]) * (Velocity[n+1] - Velocity[n]) - 0.5 * (Velocity[n] + Velocity[n-1]) * (Velocity[n] - Velocity[n-1]));
		}
	
		//Solution array update
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
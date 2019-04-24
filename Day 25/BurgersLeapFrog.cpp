/* This code will solve the Burgers' 
 * equation using the Leapfrog scheme
 * in time.
 */
 
#include <iostream>
using namespace std;

//Notes: I think the way I implemented it seems to be incorrect due to the instability.
//When checking sources, it seems the way I implemented seems to be correct.
//So my thoughts on why it appears to be instable is due to the initial condition. 
int main()
{
	//Problem statement and discretization
	double Length = 1.0;
	double TotalTime = 0.5;
	int NodeX = 200;
	int TimeStep = 5000;
	int UsedTimeStep = 1000;
	
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeStep;
	
	//Boundary conditions
	double LeftBoundary = 1.0;
	double RightBoundary = 1.0;
	
	//Initial conditions
	double TopPeak = 2.0;
	double BottomPeak = 1.0;
	
	//Array declaration 
	double VelocityVector[NodeX] = {};
	double VelocityVectorCopy[NodeX] = {};
	double VelocityVectorLeapStep[NodeX] = {};
	
	//Array initialization
	for (int n = 0; n < NodeX; n++)
	{
		if (n >= 0.4 * NodeX && n < 0.6 * NodeX)
		{
			VelocityVector[n] = TopPeak;
			VelocityVectorCopy[n] = TopPeak;
			VelocityVectorLeapStep[n] = TopPeak;
 		}
		else
		{
			VelocityVector[n] = BottomPeak;
			VelocityVectorCopy[n] = BottomPeak;
			VelocityVectorLeapStep[n] = BottomPeak;
		}
	}
	
	//First step of the leapfrod approach
	//Uses a standard FTCD approach
	for (int n = 1; n < NodeX - 1; n++)
	{
		VelocityVectorCopy[n] = VelocityVector[n] - 0.5 * DeltaTime / DeltaX * (VelocityVector[n+1] * VelocityVector[n+1] - VelocityVector[n-1] * VelocityVector[n-1]); 
	}
	
	//Actual solver step
	for (int Time = 0; Time < UsedTimeStep; Time++)
	{
		//Array update step 
		for (int n = 0; n < NodeX; n++)
		{
			VelocityVectorLeapStep[n] = VelocityVector[n];
			VelocityVector[n] = VelocityVectorCopy[n]; 
		}
		
		for (int n = 1; n < NodeX - 1; n++)
		{
			VelocityVectorCopy[n] = VelocityVectorLeapStep[n] - DeltaTime / DeltaX * (VelocityVector[n+1] * VelocityVector[n+1] - VelocityVector[n-1] * VelocityVector[n-1]);
		}
	}
	
	//Velocity array output
	for (int n = 0; n < NodeX; n++)
	{
		cout << VelocityVector[n] << "\n";
	}
	
	return 0;
}
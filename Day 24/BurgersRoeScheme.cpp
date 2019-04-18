/* This code is intended to solve the
 * 1D inviscid, Burgers' equation using 
 * the Roe flux scheme without reading much
 * notes on it first. All I have done was 
 * read a cliffnotes version of the method
 * as just a first step into the method. 
 */

#include <iostream>
#include <cmath>
using namespace std;

//Notes: Seems to be pretty stable and the solution around shocks are smooth
//Still not sure if there is any issues, but seems to be working fine even
//when compared in different cases.

double FluxCheck(double CurrentValue, double UpstreamValue);

int main()
{
	//Basic problem description and discretization
	double Length = 1.0;
	double TotalTime = 0.5;
	int NodeX = 100;
	int TimeSteps = 500;
	int UsedTimeSteps = 50;
	
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeSteps;
	
	//Boundary conditions
	double LeftBoundary = 1.0;
	double RightBoundary = 1.0;
	
	//Initial conditions
	double TopPeak = 2.0;
	double BottomPeak = 1.0;
	
	//Array declaration 
	double SolutionVector[NodeX] = {};
	double SolutionVectorCopy[NodeX] = {};
	
	//Array initialization
	for (int n = 0; n < NodeX; n++)
	{
		if (n >= 0.4 * NodeX && n < 0.6 * NodeX)
		{
			SolutionVector[n] = TopPeak;
			SolutionVectorCopy[n] = TopPeak;
		}
		else 
		{
			SolutionVector[n] = BottomPeak;
			SolutionVectorCopy[n] = BottomPeak;
		}
	}
	
	//Solution solver step
	for (int TimeCount = 0; TimeCount < UsedTimeSteps; TimeCount++)
	{
		//Spatial update and Roe Flux check
		for (int n = 1; n < NodeX - 1; n++)
		{
			double FluxCheckRight = FluxCheck(SolutionVector[n], SolutionVector[n+1]);
			double FluxCheckLeft = FluxCheck(SolutionVector[n], SolutionVector[n-1]);
		
			SolutionVectorCopy[n] = SolutionVector[n] - DeltaTime / DeltaX * ( 
									(0.5 * (0.5 * SolutionVector[n] * SolutionVector[n] + 0.5 * SolutionVector[n+1] * SolutionVector[n+1]) 
									- 0.5 * abs(FluxCheckRight) * (SolutionVector[n+1] - SolutionVector[n]))
									- 
									(0.5 * (0.5 * SolutionVector[n] * SolutionVector[n] + 0.5 * SolutionVector[n-1] * SolutionVector[n-1]) 
									- 0.5 * abs(FluxCheckRight) * (SolutionVector[n] - SolutionVector[n-1])));
		}
	
		//Boundary condition enforcement
		SolutionVectorCopy[0] = LeftBoundary;
		SolutionVectorCopy[NodeX - 1] = RightBoundary;
	
		//Solution vector update
		for (int n = 0; n < NodeX; n++)
		{
			SolutionVector[n] = SolutionVectorCopy[n];
		}
	}
	
	//Solution array output
	for (int n = 0; n < NodeX; n++)
	{
		cout << SolutionVector[n] << "\n";
	}
	
	return 0;
}

double FluxCheck(double CurrentValue, double UpstreamValue)
{
	double NumericalFlux;
	
	if (UpstreamValue != CurrentValue)
	{
		//Jacobian is a form of normalization
		NumericalFlux = 0.5 * (UpstreamValue * UpstreamValue - CurrentValue * CurrentValue) / (UpstreamValue - CurrentValue);
	}
	
	if (UpstreamValue == CurrentValue)
	{
		//When the same the Jacobian is just the average
		NumericalFlux = 0.5 * (UpstreamValue + CurrentValue);
	}
	
	return NumericalFlux;
}
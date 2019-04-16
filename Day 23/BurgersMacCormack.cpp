/* This code solves the inviscid Burgers 
 * equation using the MacCormack method
 * in 1D.
 */
 
#include <iostream>
using namespace std;

int main()
{
	//Basic problem definition.
	double Length = 1.0;
	double TotalTime = 0.5;
	int NodeX = 200;
	int TimeStep = 600;
	int TimeStepUsed = 50;
	
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / (TimeStep);
	
	//Boundary conditions
	double LeftBoundary = 1.0;
	double RightBoundary = 1.0;
	
	//Initial conditions
	double TopPeak = 2.0;
	double BottomPeak = 1.0;
	
	//Array declaration
	double SolutionVector[NodeX] = {};
	double PredictionVector[NodeX] = {};
	double SolutionVectorCopy[NodeX] = {};
	
	//Array initialization
	for (int n = 0; n < NodeX; n++)
	{
		if ( n >= 0.4 * NodeX && n < 0.6 * NodeX)
		{
			SolutionVector[n] = TopPeak;
			PredictionVector[n] = TopPeak;
			SolutionVectorCopy[n] = TopPeak;
		}
		else
		{
			SolutionVector[n] = BottomPeak;
			PredictionVector[n] = BottomPeak;
			SolutionVectorCopy[n] = BottomPeak;
		}
	}
	
	//Solver step
	for (int TimeCount = 0; TimeCount < TimeStepUsed; TimeCount++)
	{
		//Predictor step
		for (int n = 0; n < NodeX - 1; n++)
		{
			PredictionVector[n] = SolutionVector[n] - SolutionVector[n] * DeltaTime / DeltaX * (SolutionVector[n+1] - SolutionVector[n]);
		}
	
		//Correction step (boundary conditions are enforced)
		for (int n = 1; n < NodeX - 1; n++)
		{
			SolutionVectorCopy[n] = 0.5 * (SolutionVector[n] + PredictionVector[n]) 
									- 0.5 * SolutionVector[n] * DeltaTime / DeltaX * (PredictionVector[n] - PredictionVector[n-1]);
		}
	
		//Update step
		for (int n = 0; n < NodeX; n++)
		{
			SolutionVector[n] = SolutionVectorCopy[n];
		}
	}
	
	//Array output
	for (int n = 0; n < NodeX; n++)
	{
		cout << SolutionVector[n] << "\n";
	}
	
	return 0;
}
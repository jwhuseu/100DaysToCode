/* This code solves the basic 
 * inviscid, one-dimensional 
 * Burgers' equation.
 */
 
#include "FluxScheme.hpp"
#include "Solution.hpp"

void ResultsOutput(Col<double> &Vector);
 
int main()
{
	//Basic results output
	int outputscheme = 1; //0 for central diffrence, or 1 for upwind scheme
	
	//Basic problem definition 
	double Length = 1.0;
	double TotalTime = 0.5;
	int NodeX = 50;
	int TimeSteps = 200;
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeSteps;
	int SolverTimeSteps = 40;
	
	//Initial and Boundary Conditions
	double LeftShock = 2.0;
	double RightShock = 1.0;
	
	double LeftBoundary = 2.0;
	double RightBoundary = 1.0;
	
	//Solution Initialization 
	SolutionContainer Burgers;
	
	Burgers.SolutionGeneration(NodeX);
	Burgers.VectorInitialization(Burgers.ResidualVector, NodeX, LeftShock, RightShock);
	Burgers.VectorInitialization(Burgers.SolutionVector, NodeX, LeftShock, RightShock);
	
	//This section of code will test out the central difference scheme for the Burgers equation
	CentralDifference central;
	Col<double> CentTempVector = vec(NodeX, fill::zeros);
	
	for (int Time = 0; Time < SolverTimeSteps; Time++)
	{
		//This solves and stores for the flux term first
		for (int n = 1; n < NodeX - 1; n++)
		{
			Burgers.ResidualVector(n) = central.Flux(Burgers.SolutionVector, n, DeltaX);
		}
		
		//This solves the remainder of the step by multiplying the 
		//non-linear part and the DeltaTime to the residual vector
		for (int n = 1; n < NodeX - 1; n++)
		{
			CentTempVector(n) = Burgers.SolutionVector(n) - Burgers.ResidualVector(n) * Burgers.SolutionVector(n) * DeltaTime;
		}
		
		CentTempVector(0) = LeftBoundary;
		CentTempVector(NodeX - 1) = RightBoundary;
		
		//Updates the solution vector
		Burgers.SolutionVector = CentTempVector;
	}
	
	//Solution stores in the central difference temp vector
	CentTempVector = Burgers.SolutionVector;
	
	//Burgers container reset
	Burgers.VectorInitialization(Burgers.ResidualVector, NodeX, LeftShock, RightShock);
	Burgers.VectorInitialization(Burgers.SolutionVector, NodeX, LeftShock, RightShock);
	
	//This section of code will test out the upwind scheme for the Burgers equation
	UpwindScheme upwind;
	Col<double> UpwindTempVector = vec(NodeX, fill::zeros);
	
	for (int Time = 0; Time < SolverTimeSteps; Time++)
	{
		//This solves and stores for the flux term first
		for (int n = 1; n < NodeX - 1; n++)
		{
			Burgers.ResidualVector(n) = upwind.Flux(Burgers.SolutionVector, n, DeltaX);
		}
		
		//This solves the remainder of the step by multiplying the 
		//non-linear part and the DeltaTime to the residual vector
		for (int n = 1; n < NodeX - 1; n++)
		{
			UpwindTempVector(n) = Burgers.SolutionVector(n) - Burgers.ResidualVector(n) * Burgers.SolutionVector(n) * DeltaTime;
		}
		
		UpwindTempVector(0) = LeftBoundary;
		UpwindTempVector(NodeX - 1) = RightBoundary;
		
		//Updates the solution vector
		Burgers.SolutionVector = UpwindTempVector;
	}
	
	//Solution for the upwind scheme is stored in the upwind temp vector 
	UpwindTempVector = Burgers.SolutionVector;
	
	if (outputscheme == 0)
	{
		ResultsOutput(CentTempVector);
	}
	
	if (outputscheme == 1)
	{
		ResultsOutput(UpwindTempVector);
	}
	
	return 0;
}

void ResultsOutput(Col<double> &Vector)
{
	cout << "The provided solution for the provided vector is: " << "\n"; 
	cout << Vector;
	cout << "\n";
}
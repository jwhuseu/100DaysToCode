/* This program is going to solve the basic shock tube 
 * problem for a quasi-1D compressible flow (Euler) equations.
 * With additional options to test out different flux calculation
 * options. The first version will deal with just the central
 * difference scheme then compare it with other schemes.
 */

#include "SolutionMatrices.hpp"
#include "FluxScheme.hpp"

void SolutionSolver();
void SolutionOutput(); 

int main()
{
	//Basic discretization and physical parameters
	double Length = 1.0;
	double TotalTime = 1.0;
	int NodeX = 10;
	int BoundaryNodes = 2;
	int TotalNodes = NodeX - BoundaryNodes;
	int TimeSteps = 20;
	
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeSteps;
	
	//Assuming the the fluid property is air.
	double AirHeatRation = 1.4;
	
	//Initial Conditions
	double DensityLeft = 1.0;
	double DensityRight = 0.125;
	
	double VelocityLeft = 0.0;
	double VelocityRight = 0.0;
	
	double PressureLeft = 1.0;
	double PressureRight = 0.1;
	
	//BoundaryConditions
	double DensityLeftBoundary = 1.0;
	double DensityRightBoundary = 0.125;
	
	double VelocityLeftBoundary = 0.0;
	double VelocityRightBoundary = 0.0;
	
	double PressureLeftBoundary = 1.0;
	double PressureRightBoundary = 0.1;
	
	
	return 0;
}
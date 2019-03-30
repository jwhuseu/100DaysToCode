/* I know that central difference scheme doesn't 
 * work for the Euler equations, this was just
 * an experiment to get something basic running.
 */

#include <iostream>

using namespace std;

void Output(double Array[], int NodeX, int TimeSteps);

int main()
{
	//Basic discretization and physical parameters
	double Length = 1.0;
	double TotalTime = 0.1;
	int NodeX = 400;
	int BoundaryNodes = 2;
	int TotalNodes = NodeX - BoundaryNodes;
	int TimeSteps = 10;
	double CFL = 0.50;
	
	double DeltaX = Length / (NodeX - 1.0);
	double DeltaTime = CFL * DeltaX;
	
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
	
	//Array declaration
	double Density[NodeX] = {};
	double Momentum[NodeX] = {};
	double Energy[NodeX] = {};
	double Velocity[NodeX] = {};
	double Pressure[NodeX] = {};
	
	double DensityCopy[NodeX] = {};
	double MomentumCopy[NodeX] = {};
	double EnergyCopy[NodeX] = {};
	double VelocityCopy[NodeX] = {};
	double PressureCopy[NodeX] = {};
	
	
	//Initial conditions
	for (int n = 0; n < NodeX; n++)
	{
		if (n <= 0.5 * NodeX)
		{
			Density[n] = DensityLeft;
			DensityCopy[n] = DensityLeft;
			
			Velocity[n] = VelocityLeft;
			VelocityCopy[n] = VelocityLeft;
			
			Pressure[n] = PressureLeft;
			PressureCopy[n] = PressureLeft;
			
			Momentum[n] = DensityLeft * VelocityLeft;
			MomentumCopy[n] = DensityLeft * VelocityLeft;
			
			Energy[n] = PressureLeft / (AirHeatRation - 1.0) + 0.5 * DensityLeft * VelocityLeft * VelocityLeft;
			EnergyCopy[n] = PressureLeft / (AirHeatRation - 1.0) + 0.5 * DensityLeft * VelocityLeft * VelocityLeft;
		}
		
		if (n > 0.5 * NodeX)
		{
			Density[n] = DensityRight;
			DensityCopy[n] = DensityRight;
			
			Velocity[n] = VelocityRight;
			VelocityCopy[n] = VelocityRight;
			
			Pressure[n] = PressureRight;
			PressureCopy[n] = PressureRight;
			
			Momentum[n] = DensityRight * VelocityRight;
			MomentumCopy[n] = DensityRight * VelocityRight;
			
			Energy[n] = PressureRight / (AirHeatRation - 1.0) + 0.5 * DensityRight * VelocityRight * VelocityRight;
			EnergyCopy[n] = PressureRight / (AirHeatRation - 1.0) + 0.5 * DensityRight * VelocityRight * VelocityRight;
		}
	}
	
	//Solver step
	for (int TimeCount = 0; TimeCount < TimeSteps; TimeCount++)
	{
		//Euler equation solvers
		for (int n = 1; n < NodeX - 1; n++)
		{
			DensityCopy[n] = Density[n] - DeltaTime / DeltaX * (Density[n + 1] * Velocity[n + 1] - Density[n - 1] * Velocity[n - 1]);
			MomentumCopy[n] = Momentum[n] - DeltaTime / DeltaX * ((Density[n + 1] * Velocity[n + 1] * Velocity[n + 1] - Pressure[n + 1]) - 
																	(Density[n - 1] * Velocity[n - 1] * Velocity[n - 1] - Pressure[n - 1]));
			EnergyCopy[n] = Energy[n] - DeltaTime / DeltaX * ((Velocity[n + 1] * Energy[n + 1] + Velocity[n + 1] * Pressure[n + 1]) - 
																(Velocity[n - 1] * Energy[n - 1] + Velocity[n - 1] * Pressure[n - 1]));
		}
		
		//Update remainder of the terms
		for (int n = 0; n < NodeX; n++)
		{
			VelocityCopy[n] = MomentumCopy[n] / Density[n];
			PressureCopy[n] = (AirHeatRation - 1.0) * (Energy[n] - 0.5 * Density[n] * Velocity[n] * Velocity[n]);
		}
		
		//Update copies 
		for (int n = 0; n < NodeX; n++)
		{
			Density[n] = DensityCopy[n];
			Momentum[n] = MomentumCopy[n];
			Energy[n] = EnergyCopy[n];
			Velocity[n] = VelocityCopy[n];
			Pressure[n] = PressureCopy[n];
		}
		
		Output(Density, NodeX, TimeCount);
	}
	
	return 0;
}

void Output(double Array[], int NodeX, int TimeSteps)
{
	cout << "The solution for " << TimeSteps << " timestep is: " << "\n";
	
	for (int n = 0; n < NodeX; n++)
	{
		cout << Array[n] << "\n";
	}
	
	cout << "\n";
}
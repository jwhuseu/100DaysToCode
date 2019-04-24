/* This code is intended to solve the 
 * 1D Euler equations with the Lax-Friedrichs 
 * scheme.
 */
 
#include <iostream>
using namespace std;

int main()
{
	//Basic problem statement and discretization
	double Length = 1.0;
	double TotalTime = 0.5;
	int NodeX = 400;
	int TimeStep = 5000;
	int UsedTimeStep = 1000;
	double GasProperty = 1.4;
	
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeStep;
	
	//Boundary conditions
	double DensityLeftBoundary = 1.0;
	double DensityRightBoundary = 0.125;
	
	double VelocityLeftBoundary = 0.0;
	double VelocityRightBoundary = 0.0;
	
	double PressureLeftBoundary = 1.0;
	double PresureRightBoundary = 0.1;
	
	//Initial conditions
	double DensityLeftShock = 1.0;
	double DensityRightShock = 0.125;
	
	double VelocityLeftShock = 0.0;
	double VelocityRightShock = 0.0;
	
	double PressureLeftShock = 1.0;
	double PresureRightShock = 0.1;
	
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

	
	//Solution array initialization 
	for (int n = 0; n < NodeX; n++)
	{
		if (n <= 0.5 * NodeX)
		{
			Density[n] = DensityLeftShock; //Density
			Momentum[n] = DensityLeftShock * VelocityLeftShock; //U-Momentum
			Energy[n] = PressureLeftShock / (GasProperty - 1) + 0.5 * DensityLeftShock * VelocityLeftShock * VelocityLeftShock; //Energy
			Pressure[n] = PressureLeftShock; //Pressure
			Velocity[n] = VelocityLeftShock; //U-Velocity
		}
		else 
		{
			Density[n] = DensityRightShock; //Density
			Momentum[n] = DensityRightShock * VelocityLeftShock; //U-Momentum
			Energy[n] = PresureRightShock / (GasProperty - 1) + 0.5 * DensityLeftShock * VelocityRightShock * VelocityRightShock; //Energy
			Pressure[n] = PresureRightShock; //Pressure
			Velocity[n] = VelocityRightShock; //U-Velocity
		}
	}
	
	//Solution array copy 
	for (int n = 0; n < NodeX; n++)
	{
		DensityCopy[n] = Density[n];
		MomentumCopy[n] = Momentum[n];
		EnergyCopy[n] = Energy[n];
	}
	
	//Solution solver
	for (int TimeCount = 0; TimeCount < UsedTimeStep; TimeCount++)
	{
		for (int n = 1; n < NodeX - 1; n++)
		{
			DensityCopy[n] = 0.5 * (Density[n+1] + Density[n-1]) - 0.5 * DeltaTime / DeltaX  * (Velocity[n+1] * Density[n+1] - Velocity[n-1] * Density[n-1]);
			MomentumCopy[n] = 0.5 * (Momentum[+1] + Momentum[n-1]) - 0.5 * DeltaTime / DeltaX * ((Density[n+1] * Velocity[n+1] * Velocity[n+1] + Pressure[n+1]) 
													- (Density[n-1] * Velocity[n-1] * Velocity[n-1] + Pressure[n-1]));
			EnergyCopy[n] = 0.5 * (Energy[n+1] + Energy[n-1]) - 0.5 * DeltaTime / DeltaX * (Velocity[n+1] * (Energy[n+1] + Pressure[n+1]) 
													- Velocity[n-1] * (Energy[n-1] + Pressure[n-1]));
		}
	
		//velocity and pressure solution vector update
		for (int n = 0; n < NodeX; n++)
		{	
			Velocity[n] = MomentumCopy[n] / DensityCopy[n];
			Pressure[n] = (GasProperty - 1) * (EnergyCopy[n] - 0.5 * DensityCopy[n] * Velocity[n] * Velocity[n]);
		}
		
		//Solution update
		for (int n = 0; n < NodeX; n++)
		{
			Density[n] = DensityCopy[n];
			Momentum[n] = MomentumCopy[n];
			Energy[n] = EnergyCopy[n];
		}
	}
	
	
	//Solution array output
	for (int n = 0; n < NodeX; n++)
	{
		if (n == 0)
		{
			cout << " Density || U-Velocity || Pressure || U-Momentum || Total Energy " << "\n";
		}
		cout << Density[n] << "    " 
			 //<< Momentum[n] << "    "
			 //<< Energy[n] << "    " 
			 //<< Velocity[n] << "    "
			 //<< Pressure[n] << "    " 
			 << "\n";
	}
	
	return 0;
}
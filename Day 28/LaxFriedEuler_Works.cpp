/* This code is intended to solve the 
 * 1D Euler equations with the Lax-Friedrichs 
 * scheme.
 */
 
#include <iostream>
using namespace std;

//I think I failed to implement this correctly. Will check later.
int main()
{
	//Basic problem statement and discretization
	double Length = 1.0;
	double TotalTime = 0.5;
	int NodeX = 400;
	int TimeStep = 500;
	int UsedTimeStep = 50;
	double GasProperty = 1.4;
	
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeStep;
	
	//Basics of the problem
	int Equation = 3; //Density, U-Momentum, and Energy
	int Variables = 5; //Density, U-Momentum, Energy, Pressure, and U-Velocity
	int ResidualSize = NodeX * Equation;
	int SolutionSize = NodeX * Variables;
	
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
	double Solution[SolutionSize] = {};
	double SolutionCopy[SolutionSize] = {};
	double Residual[ResidualSize] = {};
	
	//Solution array initialization 
	for (int n = 0; n < NodeX; n++)
	{
		if (n <= 0.5 * NodeX)
		{
			Solution[n * Variables] = DensityLeftShock; //Density
			Solution[n * Variables + 1] = DensityLeftShock * VelocityLeftShock; //U-Momentum
			Solution[n * Variables + 2] = PressureLeftShock / (GasProperty - 1) + 0.5 * DensityLeftShock * VelocityLeftShock * VelocityLeftShock; //Energy
			Solution[n * Variables + 3] = PressureLeftShock; //Pressure
			Solution[n * Variables + 4] = VelocityLeftShock; //U-Velocity
		}
		else 
		{
			Solution[n * Variables] = DensityRightShock; //Density
			Solution[n * Variables + 1] = DensityRightShock * VelocityRightShock; //U-Momentum
			Solution[n * Variables + 2] = PresureRightShock / (GasProperty - 1) + 0.5 * DensityRightShock * VelocityRightShock * VelocityRightShock; //Energy
			Solution[n * Variables + 3] = PresureRightShock; //Pressure
			Solution[n * Variables + 4] = VelocityRightShock; //U-Velocity
		}
	}
	
	//Solution array copy 
	for (int n = 0; n < SolutionSize; n++)
	{
		SolutionCopy[n] = Solution[n];
	}
	
	//Residual array initialization
	for (int n = 0; n < NodeX; n++)
	{
		Residual[n * Equation] = 0; //Density equation flux storage
		Residual[n * Equation + 1] = 0; //U-Momentum equation flux storage
		Residual[n * Equation + 2] = 0; //Energy equation flux storage
		
	}
	
	//Solution solver
	for (int TimeCount = 0; TimeCount < UsedTimeStep; TimeCount++)
	{
		//Residual vector calculation 
		for (int n = 1; n < NodeX - 1; n++)
		{
			//Density equation flux calculation
			Residual[n*Equation] = 0.5 / DeltaX * (Solution[(n+1)*Variables] * Solution[(n+1)*Variables + 4] 
												- Solution[(n-1)*Variables] * Solution[(n-1)*Variables + 4]);
			
			//U-Momentum equation flux calculation			
			Residual[n*Equation+1] = 0.5 / DeltaX * ((Solution[(n+1)*Variables]*Solution[(n+1)*Variables+4]*Solution[(n+1)*Variables+4]+Solution[(n+1)*Variables+3])
												- (Solution[(n-1)*Variables]*Solution[(n-1)*Variables+4]*Solution[(n-1)*Variables+4]+Solution[(n-1)*Variables+3]));
			
			//Energy equation flux calculation
			Residual[n*Equation+2] = 0.5 / DeltaX * (Solution[(n+1)*Variables+4]*(Solution[(n+1)*Variables+2]+Solution[(n+1)*Variables+3])
												-Solution[(n-1)*Variables+4]*(Solution[(n-1)*Variables+2]+Solution[(n-1)*Variables+3])); 										
		}
	
		//Solution vector time update
		for (int n = 1; n < NodeX - 1; n++)
		{
			SolutionCopy[n*Variables] = 0.5 * (Solution[(n+1)*Variables] + Solution[(n-1)*Variables]) - DeltaTime*Residual[n*Equation]; //Density
			SolutionCopy[n*Variables+1] = 0.5 * (Solution[(n+1)*Variables+1] + Solution[(n-1)*Variables+1]) - DeltaTime*Residual[n*Equation+1]; //U-Momentum
			SolutionCopy[n*Variables+2] = 0.5 * (Solution[(n+1)*Variables+2] + Solution[(n-1)*Variables+2]) - DeltaTime*Residual[n*Equation+2]; //Energy
		}
	
		//Pressure and velocity solution vector update
		for (int n = 1; n < NodeX - 1; n++)
		{
			SolutionCopy[n*Variables+4] = SolutionCopy[n*Variables+1] / SolutionCopy[n*Variables]; //U-Velocity
			SolutionCopy[n*Variables+3] = (GasProperty-1)*(SolutionCopy[n*Variables+2] 
																- 0.5 * SolutionCopy[n*Variables] * SolutionCopy[n*Variables+4] * SolutionCopy[n*Variables+4]); //Pressure
		}
		
		for (int n = 0; n < SolutionSize; n++)
		{
			Solution[n] = SolutionCopy[n];
		}
	}
	
	
	//Solution array output
	for (int n = 0; n < NodeX; n++)
	{
		if (n == 0)
		{
			cout << " Density || U-Velocity || Pressure || U-Momentum || Total Energy " << "\n";
		}
		cout << Solution[n * Variables] << "    " 
			 << Solution[n * Variables + 4] << "    "
			 << Solution[n * Variables + 3] << "    " 
			 << Solution[n * Variables + 1] << "    "
			 << Solution[n * Variables + 2] << "    " 
			 << "\n";
	}
	
	return 0;
}
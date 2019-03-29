/* This code is intended to solve the 1D
 * Euler equations using the Sod Shock Tube
 * problem for initial and boundary conditions.
 */
 
#include <iostream>
#include <armadillo> 

using namespace std;
using namespace arma;

//Known issues, the solution does not update anything. This could
//be due to how the values are represented in the matrix form.
//Will attempt to fix later.

class SolutionContainer
{
	public:
	Mat<double> MatrixA;
	Col<double> VecX;
	Col<double> VecB;
	
	void SolutionGeneration(int TotalNodes)
	{
		MatrixA = mat(TotalNodes, TotalNodes, fill::zeros);
		VecX = vec(TotalNodes, fill::zeros);
		VecB = vec(TotalNodes, fill::zeros);
	}
	
	void VectorInitialization(int TotalNodes, double LeftShock, double RightShock)
	{
		for (int n = 0; n < TotalNodes; n++)
		{
			if (n <= 0.5 * TotalNodes)
			{
				VecB(n) = LeftShock;
				VecX(n) = LeftShock;
			}
			
			if (n > 0.5 * TotalNodes)
			{
				VecB(n) = RightShock;
				VecX(n) = RightShock;
			}
		}
	}
	
	void BoundaryConditions();
};

class Density: public SolutionContainer
{
	public:
	void MatrixGeneration(int TotalNodes, double DeltaTime, double DeltaX, Col<double> &Density, Col<double> &Velocity)
	{
		for (int i = 0; i < TotalNodes; i++)
		{
			for (int j = 0; j < TotalNodes; j++)
			{
				if (j == i)
				{
					MatrixA(i, j) = 1.0;
				}
			
				if (j == i + 1)
				{
					MatrixA(i, j) = - Density(i) * Velocity(i) * DeltaTime / DeltaX;
				}
			
				if (j == i - 1)
				{
					MatrixA(i, j) = Density(i) * Velocity(i) * DeltaTime / DeltaX;
				} 
			}
		}
	}
};

class Momentum: public SolutionContainer
{
	public:
	void MatrixGeneration(int TotalNodes, double DeltaTime, double DeltaX, Col<double> &Density, Col<double> &Velocity, Col<double> &Pressure)
	{
		for (int i = 0; i < TotalNodes; i++)
		{
			for (int j = 0; j < TotalNodes; j++)
			{
				if (j == i)
				{
					MatrixA(i, j) = 1.0;
				}
			
				if (j == i + 1)
				{
					MatrixA(i, j) = - (Density(i) * Velocity(i) * Velocity(i) + Pressure(i)) * DeltaTime / DeltaX;
				}
			
				if (j == i - 1)
				{
					MatrixA(i, j) = (Density(i) * Velocity(i) * Velocity(i) + Pressure(i)) * DeltaTime / DeltaX;
				} 
			}
		}
	}
	
	void VectorInitialization(int TotalNodes, Col<double> &Density, Col<double> &Velocity)
	{
		for (int n = 0; n < TotalNodes; n++)
		{
			VecB(n) = Density(n) * Velocity(n);
			VecX(n) = Density(n) * Velocity(n);
		}
	}
};

class Energy: public SolutionContainer
{
	public:
	void MatrixGeneration(int TotalNodes, double DeltaTime, double DeltaX, Col<double> &Energy, Col<double> &Velocity, Col<double> &Pressure)
	{
		for (int i = 0; i < TotalNodes; i++)
		{
			for (int j = 0; j < TotalNodes; j++)
			{
				if (j == i)
				{
					MatrixA(i, j) = 1.0;
				}
			
				if (j == i + 1)
				{
					MatrixA(i, j) = - Velocity(i) * (Energy(i) + Pressure(i)) * DeltaTime / DeltaX;
				}
			
				if (j == i - 1)
				{
					MatrixA(i, j) = Velocity(i) * (Energy(i) + Pressure(i)) * DeltaTime / DeltaX;
				} 
			}
		}
	}
	
	void VectorInitialization(int TotalNodes, double FluidProperty, Col<double> &Pressure, Col<double> &Density, Col<double> &Velocity)
	{
		for (int n = 0; n < TotalNodes; n++)
		{
			VecB(n) = Pressure(n) / (FluidProperty - 1.0) + 0.5 * Density(n) * Velocity(n) * Velocity(n);
			VecX(n) = Pressure(n) / (FluidProperty - 1.0) + 0.5 * Density(n) * Velocity(n) * Velocity(n);
		}
	}
};

class Velocity: public SolutionContainer {};

class Pressure: public SolutionContainer {};

int main()
{
	//Basic discretization and physical parameters
	double Length = 1.0;
	double TotalTime = 1.0;
	int NodeX = 10;
	int BoundaryNodes = 2;
	int TotalNodes = NodeX - BoundaryNodes;
	int TimeSteps = 1000;
	
	double DeltaX = Length / (NodeX - 1.0);
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
	
	//Class constructors
	Density density;
	Momentum momentum;
	Energy energy;
	Velocity velocity;
	Pressure pressure;
	
	density.SolutionGeneration(TotalNodes);
	momentum.SolutionGeneration(TotalNodes);
	energy.SolutionGeneration(TotalNodes);
	velocity.SolutionGeneration(TotalNodes);
	pressure.SolutionGeneration(TotalNodes);
	
	//Solution initialization 
	density.VectorInitialization(TotalNodes, DensityLeft, DensityRight);
	velocity.VectorInitialization(TotalNodes, VelocityLeft, VelocityRight);
	pressure.VectorInitialization(TotalNodes, PressureLeft, PressureRight);
	
	momentum.VectorInitialization(TotalNodes, density.VecX, velocity.VecX);
	energy.VectorInitialization(TotalNodes, AirHeatRation, pressure.VecX, density.VecX , velocity.VecX);
	
	//Solution initialization
	density.MatrixGeneration(TotalNodes, DeltaTime, DeltaX, density.VecX, velocity.VecX);
	momentum.MatrixGeneration(TotalNodes, DeltaTime, DeltaX, density.VecX, velocity.VecX, pressure.VecX);
	energy.MatrixGeneration(TotalNodes, DeltaTime, DeltaX, energy.VecX, velocity.VecX, pressure.VecX);
	
	//Solver step
	for (int TimeCount = 0; TimeCount < 1; TimeCount++)
	{
		//Solution step
		density.VecB = density.MatrixA * density.VecX;
		momentum.VecB = momentum.MatrixA * momentum.VecX;
		energy.VecB = energy.MatrixA * energy.VecX;
		
		//Additional term update
		for (int n = 0; n < TotalNodes; n++)
		{
			velocity.VecB(n) = momentum.VecB(n) / density.VecB(n);
			pressure.VecB(n) = (AirHeatRation - 1.0) * (energy.VecB(n) - 0.5 * density.VecB(n) * velocity.VecB(n) * velocity.VecB(n));
		}
		
		//Vector update step
		density.VecX = density.VecB;
		momentum.VecX = momentum.VecB;
		energy.VecX = energy.VecB;
		velocity.VecX = velocity.VecB;
		pressure.VecX = pressure.VecB;
		
		//Matrix generation step
		density.MatrixGeneration(TotalNodes, DeltaTime, DeltaX, density.VecX, velocity.VecX);
		momentum.MatrixGeneration(TotalNodes, DeltaTime, DeltaX, density.VecX, velocity.VecX, pressure.VecX);
		energy.MatrixGeneration(TotalNodes, DeltaTime, DeltaX, energy.VecX, velocity.VecX, pressure.VecX);
	}
	
	cout << velocity.VecX;
	
	return 0;
}
/* This code is intended to solve the 1D
 * Euler equations using a forward difference 
 * in time and central difference in space.
 */
 
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class SolutionContainers
{
	public:
	Mat<double> Matrix;
	Col<double> VecX;
	Col<double> VecB;
	
	void SolutionGeneration(int TotalNodes);
	
	//Screwed up on my logic for the class inheritence and need to define seperate functions for the different matrices (Don't feel
	//like rewriting all the code to fix this) So I need better planning in the future. 
	void DensityMatrix(int TotalNodes, double DeltaTime, double DeltaX, double Diagonal, Col<double> &Density, Col<double> &Velocity);
	void VectorInitialization(int TotalNodes, double LeftShock, double RightShock);
	
	void BoundaryConditions(int TotalNodes, double LeftBoundary, double RightBoundary);
};	

class ConservativeContainer: public SolutionContainers
{
	public:
	void EnergyGeneration(Col<double> &Pressure, Col<double> &Density, Col<double> &Velocity, double FluidProperty, int TotalNodes);
	void MomentumGeneration(Col<double> &Density, Col<double> &Velocity, int TotalNodes);
	
	void EnergyMatrix(int TotalNodes, double DeltaTime, double DeltaX, double Diagonal, Col<double> &Energy, Col<double> &Velocity, Col<double> &Pressure);
	void MomentumMatrix(int TotalNodes, double DeltaTime, double DeltaX, double Diagonal, Col<double> &Density, Col<double> &Velocity, Col<double> &Pressure);
};

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
	
	//These classes are the basics primitive variables for the Euler equations
	SolutionContainers Density, Velocity, Pressure;
	ConservativeContainer Energy, Momentum;
	
	//Matrix and vector generation for the declared classes.
	Density.SolutionGeneration(TotalNodes);
	Velocity.SolutionGeneration(TotalNodes);
	Pressure.SolutionGeneration(TotalNodes);
	
	Energy.SolutionGeneration(TotalNodes);
	Momentum.SolutionGeneration(TotalNodes);
	
	//Initial conditions for the solutions
	Density.VectorInitialization(TotalNodes, DensityLeft, DensityRight);
	Velocity.VectorInitialization(TotalNodes, VelocityLeft, VelocityRight);
	Pressure.VectorInitialization(TotalNodes, PressureLeft, PressureRight);
	
	Energy.EnergyGeneration(Pressure.VecX, Density.VecX, Velocity.VecX, AirHeatRation, TotalNodes);
	Momentum.MomentumGeneration(Density.VecX, Velocity.VecX, TotalNodes);
	
	//Basic Euler central difference solver step
	for (int TimeCount = 0; TimeCount < TimeSteps; TimeCount++)
	{
		//Matrix generations
		Density.DensityMatrix(TotalNodes, DeltaTime, DeltaX, 1.0, Density.VecX, Velocity.VecX);
		Momentum.MomentumMatrix(TotalNodes, DeltaTime, DeltaX, 1.0, Density.VecX, Velocity.VecX, Pressure.VecX);
		Energy.EnergyMatrix(TotalNodes, DeltaTime, DeltaX, 1.0, Energy.VecX, Velocity.VecX, Pressure.VecX);
		
		//This step is where the matrix operations occur for the three conserved equations.
		Density.VecB = Density.Matrix * Density.VecX;
		Momentum.VecB = Momentum.Matrix * Momentum.VecX;
		Energy.VecB = Energy.Matrix * Energy.VecX;
		
		for (int n = 0; n < TotalNodes; n++)
		{
			Velocity.VecB(n) = Momentum.VecB(n) / Density.VecB(n); 
			Pressure.VecB(n) = (AirHeatRation - 1.0) * (Energy.VecB(n) - 0.5 * Density.VecB(n) * Velocity.VecB(n) * Velocity.VecB(n));
		}
		
		//BoundaryConditions
		Density.BoundaryConditions(TotalNodes, DensityLeftBoundary, DensityRightBoundary);
		Velocity.BoundaryConditions(TotalNodes, VelocityLeftBoundary, VelocityRightBoundary);
		Pressure.BoundaryConditions(TotalNodes, PressureLeftBoundary, PressureRightBoundary);
		
		//Store the matrices into the next step of the iteration.
		Density.VecX = Density.VecB;
		Momentum.VecX = Velocity.VecB * Density.VecB;
		Energy.VecX = Energy.VecB;
		Velocity.VecX = Velocity.VecB;
		Pressure.VecX = Pressure.VecB;
	}
	
	return 0;
}

void SolutionContainers::SolutionGeneration(int TotalNodes)
{
	Matrix = mat(TotalNodes, TotalNodes, fill::zeros);
	VecX = vec(TotalNodes, fill::zeros);
	VecB = vec(TotalNodes, fill::zeros);
}

void SolutionContainers::DensityMatrix(int TotalNodes, double DeltaTime, double DeltaX, double Diagonal, Col<double> &Density, Col<double> &Velocity)
{
	for (int i = 0; i < TotalNodes; i++)
	{
		for (int j = 0; j < TotalNodes; j++)
		{
			if (j == i)
			{
				Matrix(i, j) = Diagonal;
			}
			
			if (j == i + 1)
			{
				Matrix(i, j) = - Density(i) * Velocity(i) * DeltaTime / DeltaX;
			}
			
 			if (j == i - 1)
			{
				Matrix(i, j) = Density(i) * Velocity(i) * DeltaTime / DeltaX;
			} 
		}
	}
}

void SolutionContainers::VectorInitialization(int TotalNodes, double LeftShock, double RightShock)
{
	for (int n = 0; n < TotalNodes; n++)
	{
		if (n <= 0.5 * TotalNodes)
		{
			VecX(n) = LeftShock;
			VecB(n) = LeftShock;
		}
		
		if (n > 0.5 * TotalNodes)
		{
			VecX(n) = RightShock;
			VecB(n) = RightShock;
		}
	}
}

void SolutionContainers::BoundaryConditions(int TotalNodes, double LeftBoundary, double RightBoundary)
{
	VecB(0) = VecB(0) + LeftBoundary;
	VecB(TotalNodes - 1) = VecB(TotalNodes - 1) + RightBoundary;
}

void ConservativeContainer::EnergyGeneration(Col<double> &Pressure, Col<double> &Density, Col<double> &Velocity, double FluidProperty, int TotalNodes)
{
	for (int n = 0; n < TotalNodes; n++)
	{
		VecB(n) = Pressure(n) / (FluidProperty - 1.0) + 0.5 * Density(n) * Velocity(n) * Velocity(n);
		VecX(n) = Pressure(n) / (FluidProperty - 1.0) + 0.5 * Density(n) * Velocity(n) * Velocity(n);
	}
}

void ConservativeContainer::MomentumGeneration(Col<double> &Density, Col<double> &Velocity, int TotalNodes)
{
	for (int n = 0; n < TotalNodes; n++)
	{
		VecB(n) = Density(n) * Velocity(n);
		VecX(n) = Density(n) * Velocity(n);
	}
}

void ConservativeContainer::EnergyMatrix(int TotalNodes, double DeltaTime, double DeltaX, double Diagonal, Col<double> &Energy, Col<double> &Velocity, Col<double> &Pressure)
{
	for (int i = 0; i < TotalNodes; i++)
	{
		for (int j = 0; j < TotalNodes; j++)
		{
			if (j == i)
			{
				Matrix(i, j) = Diagonal;
			}
			
			if (j == i + 1)
			{
				Matrix(i, j) = - Velocity(i) * (Energy(i) + Pressure(i)) * DeltaTime / DeltaX;
			}
			
 			if (j == i - 1)
			{
				Matrix(i, j) = Velocity(i) * (Energy(i) + Pressure(i)) * DeltaTime / DeltaX;
			} 
		}
	}
}


void ConservativeContainer::MomentumMatrix(int TotalNodes, double DeltaTime, double DeltaX, double Diagonal, Col<double> &Density, Col<double> &Velocity, Col<double> &Pressure)
{
	for (int i = 0; i < TotalNodes; i++)
	{
		for (int j = 0; j < TotalNodes; j++)
		{
			if (j == i)
			{
				Matrix(i, j) = Diagonal;
			}
			
			if (j == i + 1)
			{
				Matrix(i, j) = - (Density(i) * Velocity(i) * Velocity(i) + Pressure(i)) * DeltaTime / DeltaX;
			}
			
 			if (j == i - 1)
			{
				Matrix(i, j) = (Density(i) * Velocity(i) * Velocity(i) + Pressure(i)) * DeltaTime / DeltaX;
			} 
		}
	}
}
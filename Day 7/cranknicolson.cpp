/* This code is intended to solve the advection equation  
   using the crank-nicolson method and also practice using
   the armadillo C++ linear algebra library built on 
   BLAS and other similar foundational tools. (Also, kinda
   tired of having to rewrite the matrix operations for each 
   new code). 
	*/

	
//Known Issues:
//Seems to solve the approach as expected, the only issue
//that I can think of with that output is that the crank-nicolson 
//does not work well with shocks and this appears correct when
//finding similar resources online. 
#include <iostream>
#include <armadillo>

//Read that using global namespaces are bad,
//but not sure how to replace that for now.
//I'll just use that for now until I work on
//larger projects.
using namespace std;
using namespace arma;

void RightMatrixGeneration(Mat<double>&Matrix, double Beta, double CFL, int NodeX);
void LeftMatrixGeneration(Mat<double>&Matrix, double Beta, double CFL, int NodeX);
void ColumnVectorInitialization(Col<double>&Column, double PeakInitial, double RegularInitial, int NodeX);

int main()
{
	//Physical quantites and discretization considerations
	double Length = 5.0;
	double Time = 10.0;
	double AdvectionConstant = 1.0;
	double EquationBetaTerm = 0.5;
	
	int NodeX = 200;
	int NodeTime = 100;
	double DeltaX = Length / (NodeX - 1);
	//double DeltaTime = Time / NodeTime;
	double DeltaTime = 0.00249;
	
	//Boundary and Initial Conditions
	double BoundaryLeft = 1.0;
	double BoundaryRight = 1.0;
	
	double PeakInitial = 2.0;
	double RegularInitial = 1.0;
	
	double CFL = AdvectionConstant * DeltaTime / DeltaX / 2.0;
	
	//Matrix and vector generation
	Mat<double> RightMatrix = mat(NodeX, NodeX, fill::zeros);
	Mat<double> LeftMatrix = mat(NodeX, NodeX, fill::zeros);
	
	Col<double> RightVector = vec(NodeX, fill::ones);
	Col<double> LeftVector = vec(NodeX, fill::ones);
	Col<double> LeftVectorCopy = vec(NodeX, fill::ones);
	
	ColumnVectorInitialization(RightVector, PeakInitial, RegularInitial, NodeX);
	RightMatrixGeneration(RightMatrix, EquationBetaTerm, CFL, NodeX); 
	LeftMatrixGeneration(LeftMatrix, EquationBetaTerm, CFL, NodeX);
	
	cout << "The original vector solution is the following: "<< endl;
	cout << RightVector;
	//Solver step of the system of equations
	
	for (int t = 0; t < NodeTime; t++)
	{
		LeftVector = LeftMatrix.i() * RightMatrix * RightVector;
		
		RightVector = LeftVector;
		
		//Enforce boundary conditions
		RightVector(0) = BoundaryLeft;
		RightVector(NodeX - 1) = BoundaryRight;
	}
	
	cout << "The solution to the Crank-Nicolson method for the advection equation is: " << endl;
	cout << RightVector;
	
	return 0;
}

void RightMatrixGeneration(Mat<double>&Matrix, double Beta, double CFL, int NodeX) 
{
	for (int i = 0; i < NodeX; i++)
	{
		for (int j = 0; j < NodeX; j++)
		{
			if (j == i)
			{
				Matrix(i, j) = 1.0;
			}
			
			if (j == i + 1)
			{
				Matrix(i, j) = Beta * CFL;
			}
			
 			if (j == i - 1)
			{
				Matrix(i, j) = -1 * Beta * CFL;
			} 
		}
	}
}
void LeftMatrixGeneration(Mat<double>&Matrix, double Beta, double CFL, int NodeX)
{
	for (int i = 0; i < NodeX; i++)
	{
		for (int j = 0; j < NodeX; j++)
		{
			if (j == i)
			{
				Matrix(i, j) = 1.0;
			}
			
			if (j == i + 1)
			{
				Matrix(i, j) = -(1 - Beta) * CFL;
			}
			
 			if (j == i - 1)
			{
				Matrix(i, j) = (1 - Beta) * CFL;
			} 
		}
	}
}

void ColumnVectorInitialization(Col<double>&Column, double PeakInitial, double RegularInitial, int NodeX)
{
	for (int n = 0; n < NodeX; n++)
	{
		if (n <= 0.5 * NodeX && n >= 0.25 * NodeX)
		{
			Column(n) = PeakInitial;
		}
		else 
		{
			Column(n) = RegularInitial;
		}
	}
}
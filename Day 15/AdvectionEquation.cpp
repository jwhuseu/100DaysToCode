/* The purpose of this program is to solve the nonlinear
 * advection equation in one dimension with basic direchlet
 * boundary conditions and a discontinuous initial  
 * condition. The method that is used is FTBS.
 */
 
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void VectorInitialization(Col<double> &Vector, int ArraySize, double LeftShock, double RightShock);
void MatrixInitialization(Mat<double> &Matrix, Col<double> Vector, int ArraySize, double DeltaX, double DeltaTime);
void SolutionSolver(Mat<double> &Matrix, Col<double> &VectorX, Col<double> &VectorB, int ArraySize, int TimeStep, double DeltaX, double DeltaTime, double LeftVelocity);

//Probably only known issue or concern is the initial condition that was selected.
//Should have probably dealt with a different signal, but the code operates as expected
//with the solution travelling forward in time.

int main()
{
	//Basic flow conditions and discretization
	double Length = 5.0;
	double Time = 1.0;
	int BoundaryNodes = 1;
	int NodeX = 50;
	int TimeStep = 100;
	
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = Time / TimeStep;
	
	int ArraySize = NodeX - BoundaryNodes;
	//Initial and Boundary Conditions
	double LeftVelocity = 2.0;
	double RightVelocity = 1.0;
	
	double LeftShock = 2.0;
	double RightShock = 1.0;
	
	//Matrix and vector container generation
	Mat<double> MatrixA = mat(ArraySize, ArraySize, fill::zeros);
	Col<double> VectorX = vec(ArraySize, fill::zeros);
	Col<double> VectorB = vec(ArraySize, fill::zeros);
	
	//The matrix and vector initilization
	VectorInitialization(VectorX, ArraySize, LeftShock, RightShock);
	VectorInitialization(VectorB, ArraySize, LeftShock, RightShock);
	
	MatrixInitialization(MatrixA, VectorX, ArraySize, DeltaX, DeltaTime);
	
	//Solution solver step
	SolutionSolver(MatrixA, VectorX, VectorB, ArraySize, TimeStep, DeltaX, DeltaTime, LeftVelocity);
	
	//Solution output
	cout << "The solution for the nonlinear convection problem is as follows: "<< "\n";
	cout << VectorX;

	return 0;
}

void VectorInitialization(Col<double> &Vector, int ArraySize, double LeftShock, double RightShock)
{
	for (int n = 0; n < ArraySize; n++)
	{
		if (n < 0.5 * ArraySize)
		{
			Vector(n) = LeftShock;
		}
		
		if (n >= 0.5 * ArraySize)
		{
			Vector(n) = RightShock;
		}
	}
}

void MatrixInitialization(Mat<double> &Matrix, Col<double> Vector, int ArraySize, double DeltaX, double DeltaTime)
{
	for (int i = 0; i < ArraySize; i++)
	{
		for (int j = 0; j < ArraySize; j++)
		{
			if (j == i)
			{
				Matrix(i,j) = 1 - Vector(i) * DeltaTime / DeltaX;
			}
			
			if (j == i - 1)
			{
				Matrix(i, j) = Vector(i) * DeltaTime / DeltaX;
			}
		}
	}
}

void SolutionSolver(Mat<double> &Matrix, Col<double> &VectorX, Col<double> &VectorB, int ArraySize, int TimeStep, double DeltaX, double DeltaTime, double LeftVelocity)
{
	for (int BeginTime = 0; BeginTime < TimeStep; BeginTime++)
	{
		VectorB = Matrix * VectorX;
		
		//Boundary condition
		VectorB(0) += VectorX(0) * LeftVelocity * DeltaTime / DeltaX;
		
		VectorX = VectorB;
		
		MatrixInitialization(Matrix, VectorX, ArraySize, DeltaX, DeltaTime);
	}
}
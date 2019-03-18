/* This is a basic program that solves the 
 * Inviscid, 1D Burger's equation by using the 
 * vertex-centered FV method.
 */

 
//This isn't finished today... spent time reading up on the general matrix form
//and differences in how some textbooks present the discretization time.
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void MatrixGeneration(Mat<double> &MatrixA, Col<double> &Vector, int NodeX, double DeltaX, double DeltaTime);
void VectorInitialConditions(Col<double> &Vector, int NodeX, double LeftShock, double RightShock);

int main()
{
	//Physical setup and basic discretization schemes
	double Length = 10.0;
	double TotalTime = 10.0;
	int NodeX = 50;
	int TimeStep = 3000;
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeStep;
	
	//Boundary Conditions
	double VelocityLeft = 1.0;
	double VelocityRight = 0.0;
	
	//Initial Conditions
	double LeftShock = 1.0;
	double RightShock = 0.0;
	
	//Matrix and vector container generation
	Mat<double> MatrixA = mat(NodeX - 2, NodeX - 2, fill::zeros);
	Col<double> VectorX = vec(NodeX - 2, fill::zeros);
	Col<double> VectorB = vec(NodeX - 2, fill::zeros);
	
	//Basic test before initialization
	
	cout << "The x Vector of system Ax = b is: "<< "\n";
	cout << VectorX;
	
	VectorInitialConditions(VectorX, NodeX, LeftShock, RightShock);
	
	cout << "The x vector has been initialized as follows: " << "\n";
	cout << VectorX;
	
	//The matrix output before generation then output of the matrix after generation
	
	cout << "The default matrix is as follows: " << "\n";
	cout << MatrixA;
	
	MatrixGeneration(MatrixA, VectorX, NodeX, DeltaX, DeltaTime);
	
	cout << "The matrix of A is now generated: "<< "\n";
	cout << MatrixA;
	
	//Solver step
	for (int Time = 0; Time < 1; Time++)
	{
		VectorB = MatrixA * VectorX;
		
		//Boundary Condition modification of the solution column vector
		VectorB(0) = VectorB(0) + VectorX(0) * VelocityLeft * DeltaTime / DeltaX;
		VectorB(NodeX - 3) = VectorB(NodeX - 3) + VectorX(NodeX - 3) * VelocityRight * DeltaTime / DeltaX;
		
		//The solution column vector will be used to replace the multiplying column vector x
		
		VectorX = VectorB;
		
		//The Burgers' equation is nonlinear so the matrix itself has to be updated.
		MatrixGeneration(MatrixA, VectorX, NodeX, DeltaX, DeltaTime);
	}
	
	cout << "The solution to the Burgers' Equation is as follows: "<< "\n";
	cout << VelocityLeft << "\n";
	cout << VectorX;
	cout << VelocityRight << "\n";
	
	return 0;
}


void MatrixGeneration(Mat<double> &MatrixA, Col<double> &Vector, int NodeX, double DeltaX, double DeltaTime)
{
	for (int i = 0; i < NodeX - 2; i++)
	{
		for (int j = 0; j < NodeX - 2; j++)
		{
			if (j == i)
			{
				MatrixA(i, j) = 1.0;
			}
			
			if (j == i + 1)
			{
				MatrixA(i, j) = - Vector(i) * DeltaTime / DeltaX;
			}
			
 			if (j == i - 1)
			{
				MatrixA(i, j) = Vector(i) * DeltaTime / DeltaX;
			} 
		}
	}
}

void VectorInitialConditions(Col<double> &Vector, int NodeX, double LeftShock, double RightShock)
{
	for (int n = 0; n < NodeX - 2; n++)
	{
		if (n < 0.5 * NodeX - 2)
		{
			Vector(n) = LeftShock;
		}
		
		if (n >= 0.5 * NodeX - 2)
		{
			Vector(n) = RightShock;
		}
	}
}
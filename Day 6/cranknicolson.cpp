/* This code is intended to solve the advection equation  
   using the crank-nicolsen method and also practice using
   the armadillo C++ linear algebra library built on 
   BLAS and other similar foundational tools. (Also, kinda
   tired of having to rewrite the matrix operations for each 
   new code). 
	*/

#include <iostream>
#include <armadillo>

//Read that using global namespaces are bad,
//but not sure how to replace that for now.
//I'll just use that for now until I work on
//larger projects.
using namespace std;
using namespace arma;

void RightMatrixGeneration();
void LeftMatrixGeneration();
void ColumnVectorInitialization(Col<double>&Column, double PeakInitial, double RegularInitial, int NodeX);

int main()
{
	//Physical quantites and discretization considerations
	double Length = 1.0;
	double Time = 10.0;
	double AdvectionConstant = 1.0;
	double EquationBetaTerm = 0.5;
	
	int NodeX = 10;
	int NodeTime = 20;
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = Time / NodeTime;
	
	//Boundary and Initial Conditions
	double BoundaryLeft = 1.0;
	double BoundaryRight = 1.0;
	
	double PeakInitial = 2.0;
	double RegularInitial = 1.0;
	
	double r = AdvectionConstant * DeltaTime / DeltaX / 2.0;
	
	//Matrix and vector generation
	Mat<double> RightMatrix = mat(NodeX, NodeX, fill::zeros);
	Mat<double> LeftMatrix = mat(NodeX, NodeX, fill::zeros);
	
	Col<double> RightVector = vec(NodeX, fill::ones);
	Col<double> LeftVector = vec(NodeX, fill::ones);
	Col<double> LeftVectorCopy = vec(NodeX, fill::ones);
	
	ColumnVectorInitialization(RightVector, PeakInitial, RegularInitial, NodeX);
	
	cout << RightVector << endl;
	
	return 0;
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
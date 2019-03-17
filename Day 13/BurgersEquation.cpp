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

void MatrixGeneration();
void VectorGeneration();
void VectorInitialConditions();

int main()
{
	//Physical setup and basic discretization schemes
	double Length = 10.0;
	double TotalTime = 10.0;
	int NodeX = 20;
	int TimeStep = 50;
	double DeltaX = Length / (NodeX - 1);
	double DeltaTime = TotalTime / TimeStep;
	
	//Boundary Conditions
	double VelocityLeft = 2.0;
	double VelocityRight = 1.0;
	
	//Initial Conditions
	double LeftShock = 2.0;
	double RightShock = 1.0;
	
	//Matrix and vector container generation
	Mat<double> MatrixA = mat(NodeX, NodeX, fill::zeros);
	Col<double> VectorX = vec(NodeX, fill::zeros);
	Col<double> VectorB = vec(NodeX, fill::zeros);
	
	
	return 0;
}
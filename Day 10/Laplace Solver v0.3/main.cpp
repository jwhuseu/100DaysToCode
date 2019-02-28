#include <iostream>
#include "Disc_Geometry.hpp"
#include "Material.hpp"
#include "Matrix_Setup.hpp"
#include "Solver.hpp"
using namespace std; 

//Known issues:
//Need to find a way to interweeve the terms better as this
//is basically just the same method except with more steps.
//Also, forgot to add the iteration count and output for error
//or residuals. 
int main()
{
	Geometry Geo;
	Discretization Disc;
	Material Mat;
	MatrixSetup Matrix;
	Solver Solve;
	
	//Problem Statement for the 2D steady state laplace equation
	double Length = 2.0;
	double Height = 2.0;
	
	Geo.GeometryDefinition(Length, Height);
	
	int NodeX = 5;
	int NodeY = 5;
	int GhostNodeX = 2;
	int GhostNodeY = 2;
	
	double DeltaX = Geo.Length / (NodeX - 1);
	double DeltaY = Geo.Height / (NodeY - 1);
	
	Disc.DiscretizationDefinition(NodeX, NodeY, GhostNodeX, GhostNodeY, DeltaX, DeltaY);
	
	double DiffusionCoefficient = 1.0;
	
	//Boundary and initial conditions
	double TopBoundaryCondition = 20.0;
	double BottomBoundaryCondition = 0.0;
	double LeftBoundaryCondition = 0.0;
	double RightBoundaryCondition = 0.0;
	double InitialCondition = 10.0;
	
	Matrix.BoundaryandInitialConditionDefinition(TopBoundaryCondition, BottomBoundaryCondition, LeftBoundaryCondition, RightBoundaryCondition, InitialCondition);
	Matrix.MatrixGeneration(Disc.NodeX, Disc.NodeY, Disc.GhostNodeX, Disc.GhostNodeY);
	Matrix.Top_BottomBoundaryConditions(Disc.NodeX, Disc.NodeY, Disc.GhostNodeX, Disc.GhostNodeY);
	Matrix.Left_RightBoundaryConditions(Disc.NodeX, Disc.NodeY, Disc.GhostNodeX, Disc.GhostNodeY);
	Matrix.InitialConditions(Disc.NodeX, Disc.NodeY, Disc.GhostNodeX, Disc.GhostNodeY);
	
	cout << "The initial matrix to be solved is the following: " << endl;
	cout << Matrix.LaplaceMatrix;
	
	//Solver step 
	Solve.SteadyStateLaplaceSolver(Matrix.LaplaceMatrix, Disc.NodeX, Disc.NodeY, Disc.GhostNodeX, Disc.GhostNodeY, Disc.DeltaX, Disc.DeltaY);
	
	cout << "The solved matrix is as follows: " << endl;
	cout << Matrix.LaplaceMatrix;
	
	return 0;
}
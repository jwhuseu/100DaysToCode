#ifndef MATRIX_SETUP
#define MATRIX_SETUP

#include <armadillo>

class MatrixSetup
{
	private:
	double TopBoundaryCondition;
	double BottomBoundaryCondition;
	double LeftBoundaryCondition;
	double RightBoundaryCondition;
	double BasicInitialCondition;
	
	public:
	double InitialandBoundaryConditionDefinition();
	double MatrixGeneration();
	double Top_BottomBoundaryConditions();
	double Left_RightBoundaryConditions();
	double InitialConditions();
};
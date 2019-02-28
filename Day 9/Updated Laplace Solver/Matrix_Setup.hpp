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
	
	Mat<double> LaplaceMatrix; //Error
	
	double BoundaryandInitialConditionDefinition(double DefaultTopBoundary = 1, double DefaultBottomBoundary = 1, double DefaultLeftBoundary = 1, double DefaultRightBoundary = 1,
												double InitialConditionFill = 1);
	double MatrixGeneration(int DefaultNodeX = 10, int DefaultNodeY = 10, int DefaultGhostNodeX = 2, int DefaultGhostNodeY = 2);
	double Top_BottomBoundaryConditions(int DefaultNodeX = 10, int DefaultNodeY = 10, int DefaultGhostNodeX = 2, int DefaultGhostNodeY = 2);
	double Left_RightBoundaryConditions(int DefaultNodeX = 10, int DefaultNodeY = 10, int DefaultGhostNodeX = 2, int DefaultGhostNodeY = 2);
	double InitialConditions(int DefaultNodeX = 10, int DefaultNodeY = 10, int DefaultGhostNodeX = 2, int DefaultGhostNodeY = 2);
};

#endif
#ifndef SOLVER
#define SOLVER

#include "Matrix_Setup.hpp"

class Solver
{
	public:
	double SteadyStateLaplaceSolver(Mat<double> &Matrix, int NodeX, int NodeY, int GhostNodeX, int GhostNodeY, double DeltaX, double DeltaY);
};

#endif
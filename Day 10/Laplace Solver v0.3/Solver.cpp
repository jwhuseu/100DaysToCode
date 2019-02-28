#include "Solver.hpp"

double Solver::SteadyStateLaplaceSolver(Mat<double> &Matrix, int NodeX, int NodeY, int GhostNodeX, int GhostNodeY, double DeltaX, double DeltaY)
{
	for (int iter = 0; iter < 10; iter++)
	{
		for (int i = 1; i < NodeX + GhostNodeX - 1; i++)
		{
			for (int j = 1; j < NodeY + GhostNodeY - 1; j++)
			{
				Matrix(j,i) = (DeltaY * DeltaY * (Matrix(j,i+1) + Matrix(j,i-1)) + 
								DeltaX * DeltaX * (Matrix(j+1,i) + Matrix(j-1,i))) / (2 * DeltaX * DeltaX + 2 * DeltaY * DeltaY);
			}
		}
	}
}
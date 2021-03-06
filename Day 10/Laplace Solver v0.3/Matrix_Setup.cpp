#include "Matrix_Setup.hpp"

double MatrixSetup::BoundaryandInitialConditionDefinition(double DefaultTopBoundary, double DefaultBottomBoundary, double DefaultLeftBoundary, double DefaultRightBoundary,
												double InitialConditionFill)
{
	TopBoundaryCondition = DefaultTopBoundary;
	BottomBoundaryCondition = DefaultBottomBoundary;
	LeftBoundaryCondition = DefaultLeftBoundary;
	RightBoundaryCondition = DefaultRightBoundary;
	BasicInitialCondition = InitialConditionFill;
}

double MatrixSetup::MatrixGeneration(int DefaultNodeX, int DefaultNodeY, int DefaultGhostNodeX, int DefaultGhostNodeY)
{
	LaplaceMatrix = mat(DefaultNodeX + DefaultGhostNodeX, DefaultNodeY + DefaultGhostNodeY, fill::zeros);
}

double MatrixSetup::Top_BottomBoundaryConditions(int DefaultNodeX, int DefaultNodeY, int DefaultGhostNodeX, int DefaultGhostNodeY)
{
	for (int i = 1; i < DefaultNodeX + DefaultGhostNodeX - 1; i++)
	{
		LaplaceMatrix(0, i) = TopBoundaryCondition;
		LaplaceMatrix(DefaultNodeY + DefaultGhostNodeY - 1, i) = BottomBoundaryCondition;
	}
}

double MatrixSetup::Left_RightBoundaryConditions(int DefaultNodeX, int DefaultNodeY, int DefaultGhostNodeX, int DefaultGhostNodeY)
{
	for (int j = 1; j < DefaultNodeY + DefaultGhostNodeY - 1; j++)
	{
		LaplaceMatrix(j, 0) = LeftBoundaryCondition;
		LaplaceMatrix(j, DefaultNodeX + DefaultGhostNodeX - 1) = RightBoundaryCondition;
	}
}

double MatrixSetup::InitialConditions(int DefaultNodeX, int DefaultNodeY, int DefaultGhostNodeX, int DefaultGhostNodeY)
{
	for (int i = 1; i < DefaultNodeX + DefaultGhostNodeX - 1; i++)
	{
		for (int j = 1; j < DefaultNodeY + DefaultGhostNodeY - 1; j++)
		{
			LaplaceMatrix(j, i) = BasicInitialCondition;
		}
	}
}
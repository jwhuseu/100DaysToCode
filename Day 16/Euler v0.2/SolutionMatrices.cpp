/* This contains the full definitions of the 
 * clas functions from SolutionMatrices.cpp
 * file.
 */
 
#include "SolutionMatrices.hpp"

void SolutionMatrices::DensityGenerationMatrix()
{
}

void SolutionMatrices::MomentumGenerationMatrix()
{
}

void SolutionMatrices::EnergyGenerationMatrix()
{
}

void SolutionVectors:: ShockTubeGenerationVector(Col<double> &Vector, int ArraySize, double LeftShock, double RightShock)
{
	for (int n = 0; n < ArraySize; n++)
	{
		if (n <= 0.5 * ArraySize)
		{
			Vector(n) = LeftShock;
		}
		
		if (n > 0.5 * ArraySize)
		{
			Vector(n) = RightShock;
		}
	}
}

void SolutionVectors::VelocityGenerationVector(Col<double> &Velocity, Col<double> &Momentum, Col<double> &Density, int ArraySize)
{
	for (int n = 0; n < ArraySize; n++)
	{
		Velocity(n) = Momentum(n) / Density(n);
	}
}

void SolutionVectors::EnergyGenerationVector(Col<double> &Energy, Col<double> &Density, Col<double> &Velocity, 
										Col<double> &Pressure, int ArraySize, double AirHeatRatio)
{
	for (int n = 0; n < ArraySize; n++)
	{
		Energy(n) = Pressure(n) / (AirHeatRatio - 1.0) + 0.5 * Density(n) * Velocity(n) * Velocity(n);
	}
}
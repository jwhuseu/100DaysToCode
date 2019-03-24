/* This section of code will deal with the matrix
 * generation of the three conservative values 
 * of density, velocity, and energy for the 
 * 1D Euler equations.
 */

#ifndef SOLUTIONMATRICES
#define SOLUTIONMATRICES

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class SolutionMatrices
{
	public: 
	Mat<double> DensityMatrix;
	Mat<double> MomentumMatrix;
	Mat<double> EnergyMatrix;
	
	//class methods
	void DensityGenerationMatrix();
	void MomentumGenerationMatrix();
	void EnergyGenerationMatrix();
};

class SolutionVectors
{
	public:
	Col<double> DensityVector;
	Col<double> MomentumVector;
	Col<double> PressureVector;
	Col<double> VelocityVector;
	Col<double> EnergyVector;
	
	//class methods
	void ShockTubeGenerationVector(Col<double> &Vector, int ArraySize, double LeftShock, double RightShock);
	void VelocityGenerationVector(Col<double> &Velocity, Col<double> &Momentum, Col<double> &Density, int ArraySize);
	void EnergyGenerationVector(Col<double> &Energy, Col<double> &Density, Col<double> &Velocity, 
								Col<double> &Pressure, int ArraySize, double AirHeatRatio);
};


#endif

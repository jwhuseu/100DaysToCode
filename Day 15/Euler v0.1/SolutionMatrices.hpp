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
	Mat<double> PressureMatrix; //Might need this for future use depending on how I treat the pressure term.
	
	//class methods
	void DensityGenerationMatrix();
	void MomentumGenerationMatrix();
	void EnergyGenerationMatrix();
	void PressureGenerationMatrix();
};

class SolutionVectors
{
	public:
	Col<double> DensityVector;
	Col<double> MomentumVector;
	Col<double> EnergyVector;
	Col<double> PressureVector; //Will keep depending on how the pressure is solved for.
	
	//class methods
	void DensityGenerationVector();
	void MomentumGenerationVector();
	void EnergyGenerationVector();
	void PressureGenerationVector();
};


#endif

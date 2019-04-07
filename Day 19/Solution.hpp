/* This basic code is used for the 
 * basics of the containers that will
 * be used.
 */

#ifndef SOLUTION
#define SOLUTION
 
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class SolutionContainer
{
	public:
	Col<double> ResidualVector;
	Col<double> SolutionVector;
	
	void SolutionGeneration(int NodePoints);
	void VectorInitialization(Col<double> &Vector, int NodePoints, double LeftShock, double RightShock);
};

void SolutionContainer::SolutionGeneration(int NodePoints)
{
	ResidualVector = vec(NodePoints, fill::zeros);
	SolutionVector = vec(NodePoints, fill::zeros);
}

void SolutionContainer::VectorInitialization(Col<double> &Vector, int NodePoints, double LeftShock, double RightShock)
{
	for (int n = 0; n < NodePoints; n++)
	{
		if (n <= 0.5 * NodePoints)
		{
			Vector(n) = LeftShock;
		}
		
		if (n > 0.5 * NodePoints)
		{
			Vector(n) = RightShock;
		}
	}
}

#endif
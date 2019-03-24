/* This portion of code will deal with
 * the flux term in the Euler equations 
 * where there will different options
 * on the scheme. 
 */

#ifndef FLUXSCHEME
#define FLUXSCHEME

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class FluxScheme
{
	public:
	Mat<double> JacobianMatrix;
	
	void CentralDifference();
	void LaxFriedrichs();
	void LaxWendroff();
	void JacobianGenerationMatrix();
};

#endif 
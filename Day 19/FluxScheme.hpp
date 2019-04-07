/* This code is the header file for the 
 * basic flux term handling file.
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
	double Flux(Col<double> &Vector, int IterationNumber, double DeltaX);
};

class CentralDifference: public FluxScheme
{
	public:
	double Flux(Col<double> &Vector, int IterationNumber, double DeltaX);
};

class UpwindScheme: public FluxScheme
{
	public:
	double Flux(Col<double> &Vector, int IterationNumber, double DeltaX);
};

double CentralDifference::Flux(Col<double> &Vector, int IterationNumber, double DeltaX)
{
	return (Vector(IterationNumber+1) - Vector(IterationNumber-1))/DeltaX;
}

double UpwindScheme::Flux(Col<double> &Vector, int IterationNumber, double DeltaX)
{
	return (Vector(IterationNumber) - Vector(IterationNumber-1))/DeltaX;
}


#endif
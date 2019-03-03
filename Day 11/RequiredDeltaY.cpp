/* This is a code example for generating the required deltaY for a given Reynolds number, 
 * where Reynolds number of a flat plate is Re = U * x / Viscosity 
 * Boundary layer thickness approximate of x / sqrt (Re).
 * sqrt (Re) = deltaY / deltaX. So deltaY / deltaX = BL thickness / x. 
 *
 */
 
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	//General physical properties
	double Length = 5.0;
	double FreestreamVelocity = 1.0;
	double DynamicViscosity = 1.0;
	double ReynoldsNumber = FreestreamVelocity * Length / DynamicViscosity;
	double BoundaryLayerThickness = Length / sqrt(ReynoldsNumber);
	
	//Discretization
	int NodeX = 100;
	double DeltaX = Length / (NodeX - 1);
	double DeltaY = DeltaX / sqrt(ReynoldsNumber);
	
	cout << "The required DeltaY for the given DeltaX of " << DeltaX << " is " << DeltaY << "\n";
	cout << "The ratio for the Reynolds number " << ReynoldsNumber << " is " << DeltaX / DeltaY << "\n";
	
	ReynoldsNumber = 1000000;
	DeltaX = Length / (NodeX - 1);
	DeltaY = DeltaX / sqrt(ReynoldsNumber);
	cout << "The required DeltaY for the given DeltaX of " << DeltaX << " is " << DeltaY << "\n";
	cout << "The ratio for the Reynolds number " << ReynoldsNumber << " is " << DeltaX / DeltaY << "\n";
	
	return 0;
}
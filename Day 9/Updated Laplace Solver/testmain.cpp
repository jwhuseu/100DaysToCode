/* This is the test main that will be 
   be used to test certain functionality 
   of the header files and how they interact.*/

#include <iostream>
#include "Disc_Geometry.hpp"
#include "Material.hpp"
using namespace std; 
int main()
{
	//First test involves calling the GeometryDefinition function and 
	//output the default values first then the second test will out be
	//modifying the input variables.

	Geometry Geo;

	Geo.GeometryDefinition();
	
	cout << "The default length and height are the following: " << endl;
	cout << "The default length is: " << Geo.Length << endl;
	cout << "The default height is: " << Geo.Height << endl;
	cout << endl;

	double TestLength = 5;
	double TestHeight = 10;
	
	Geo.GeometryDefinition(TestLength, TestHeight);
	
	cout << "The modified length and height are the following: "<< endl;
	cout << "The modified length is: " << Geo.Length << endl;
	cout << "The modified height is: " << Geo.Height << endl;
	cout << endl;
	
	//This is the second test that will be calling the DiscretizationDefinition
	//function and output the default values and the additional modified values
	//that will be provided to the function.
	
	Discretization Disc;
	
	Disc.DiscretizationDefinition();
	
	cout << "The default discretization is as follows: " << endl;
	cout << "The default NodeX is: " << Disc.NodeX << endl;
	cout << "The default NodeY is: " << Disc.NodeY << endl;
	cout << "The default GhostNodeX is: " << Disc.GhostNodeX << endl;
	cout << "The default GhostNodeY is: " << Disc.GhostNodeY << endl;
	cout << "The default DeltaX is: " << Disc.DeltaX << endl;
	cout << "The default DeltaY is: " << Disc.DeltaY << endl;
	cout << endl;
	
	double TestNodeX = 2;
	double TestNodeY = 3;
	double TestGhostNodeX = 4;
	double TestGhostNodeY = 5;
	double TestDeltaX = 6;
	double TestDeltaY = 7;
	
	Disc.DiscretizationDefinition(TestNodeX, TestNodeY, TestGhostNodeX, TestGhostNodeY, TestDeltaX, TestDeltaY);   
	
	cout << "The test discretization is as follows: " << endl;
	cout << "The test NodeX is: " << Disc.NodeX << endl;
	cout << "The test NodeY is: " << Disc.NodeY << endl;
	cout << "The test GhostNodeX is: " << Disc.GhostNodeX << endl;
	cout << "The test GhostNodeY is: " << Disc.GhostNodeY << endl;
	cout << "The test DeltaX is: " << Disc.DeltaX << endl;
	cout << "The test DeltaY is: " << Disc.DeltaY << endl;
	cout << endl;
	
	//This is the third test that will handle material definitions using
	//the MaterialDefinition Function.
	
	Material Mat;
	
	Mat.MaterialDefinition();
	
	cout << "The default material value is as follows: " << endl;
	cout << "The default material value is: " << Mat.DiffusionCoefficient << endl;
	cout << endl;
	
	double TestDiffusionCoefficient = 4;
	
	Mat.MaterialDefinition(TestDiffusionCoefficient);
	
	cout << "The test material value is as follows: " << endl;
	cout << "The test material value is: " << Mat.DiffusionCoefficient << endl;
	cout << endl;
	
	return 0;
}
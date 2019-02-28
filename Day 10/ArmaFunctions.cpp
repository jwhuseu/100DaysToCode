/* This code is intended to test out different functionalities
   of the armadillo libraries and see how to output the results
   and what the outfile looks like. Plus this forces me to 
   read more of the documentation. */
   
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
	Cube<double> CubeMatrix = cube(5,5,5);
	
	Mat<double> MatrixTest = mat(10,10,fill::ones);
	
	cout << "The Matrix row number amount is: " << MatrixTest.n_rows << endl;
	cout << "The Matrix column number amount is: " << MatrixTest.n_cols << endl;
	cout << "The amount of Matrix elements is: " << MatrixTest.n_elem << endl;
	cout << MatrixTest;
	cout << endl;
	
	double Filler = 100;
	cout << "The fill amount is as follows: " << Filler << endl;
	MatrixTest.fill(Filler);
	cout << MatrixTest;
	cout << endl;
	
	//TIME TO CREATE AN IDENTITY MATRIX
	cout << "The identity matrix is formed: " << endl;
	mat Identity = eye<mat>(5,5);
	cout << Identity;
	return 0;
}
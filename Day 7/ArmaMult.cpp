/* This is just a code example to see 
   how armadillo handles matrix-vector multiplication.
   Mostly see if I need to declare a new vector
   as a container or if a new variable takes over.*/

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
	Mat<double> MatrixA = mat(5,5, fill::ones);
	Col<double> VectorX = vec(5, fill::zeros);
	
	cout << "The generated matrix is the following: "<< endl;
	cout << MatrixA;
	
	cout << "The following vector is: "<< endl;
	cout << VectorX;
	
	cout << "The Matrix A is multiplied by Vector X as A * x; " << endl;
	cout << MatrixA * VectorX;
	
	cout << "The resulting vector is stored in the following form of Vector B: " << endl;
	Col<double> VectorB = MatrixA * VectorX;
	cout << VectorB;
	
	//Only issue that was encountered was attempting to compile and forgot the -larmdillo tag
	return 0;
}
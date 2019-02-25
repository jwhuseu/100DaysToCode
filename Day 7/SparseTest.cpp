/* This code is to test out some basic armadillo
   functionality as well as see what issues that 
   I had earlier with implementing the sparse solver
   function.*/
   
//Known Issues:
//Code gets a memory dump when using spsolve and needs
//SuperLU to be enabled. Need some more basic reading for 
//using additional compiler flags. Will come back to this 
//later and just pretend all the matrices generated are 
//juse dense matrices.
   
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
	int size = 5;
	sp_mat A = speye(size,size); //Sets an identity matrix
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j == i + 1)
			{
				A(i,j) = 2;
			}
		}
	}
	
	//Vector declaration that will be used for testing the sparse solver function
	
	Col<double> VectorB = vec(size, fill::ones);
	Col <double> VectorX = vec (size, fill::ones);
	
	VectorX = spsolve(A, VectorB, "superlu");
	
	cout << VectorX; 
	return 0;
}
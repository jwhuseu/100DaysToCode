/* This is an example of the sparse matrix
 * options in the Eigen library.
 *
 */
 
#include <iostream>
#include <Eigen/Sparse>
#include <vector>

using namespace std;
using namespace Eigen;

int main()
{
	SparseMatrix<int> A(5, 5);
	
	vector< Triplet<int> > triplets;
	
	//Triplets are a data type that hold 
	//the position of the value in terms of matrix position
	//(i,j) notation.
	
	//set_back() is a vector function that adds or copies 
	//a value to the last element in the vector array.
	//The vector format is a n by 3 array? I'm guessing here.
	triplets.push_back(Triplet<int>(0, 1, 3));
	triplets.push_back(Triplet<int>(1, 0, 22));
	triplets.push_back(Triplet<int>(2, 1, 5));
	triplets.push_back(Triplet<int>(2, 3, 1));
	triplets.push_back(Triplet<int>(4, 2, 14));
	triplets.push_back(Triplet<int>(4, 4, 8));
	triplets.push_back(Triplet<int>(2, 2, 100));
	
	A.setFromTriplets(triplets.begin(), triplets.end());
	
	A.insert(0, 0);
	A.makeCompressed();
	
	cout << "\n" << A; 
	
	
	return 0;
}
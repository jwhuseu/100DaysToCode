#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class Matrix 
{
	public:
	Mat<double> A = randu(4,4);
};

int main()
{
	Matrix Test1, Test2;
	
	cout << Test1.A << endl;
	
	cout << Test2.A << endl;
	
	return 0;
}
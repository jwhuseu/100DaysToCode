#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main()
{
	//Defining a 3x3 matrix of floats
	Matrix3f A;
	A << 1, 0, 1,
		 2, 5, 0,
		 1, 1, 2;
	
	cout << "Matrix A: " << "\n" << A << "\n";
	
	//Access to element (1,1) of matrix Access
	
	cout << "A[1,1]:" << "\n" << A(1,1) << "\n";
	
	//Vector of size 3, made of floats
	Vector3f B;
	B << 1, 0, 1;
	
	cout << "Vector B:" << "\n" << B << "\n";
	
	//Access of vector element [1]
	
	cout << "Vector B[1]: " << "\n" << B(1) << "\n";
	
	//Basic vector multiplication
	
	Vector3f C = A * B;
	cout << "C = A  * B: " << "\n" << C << "\n";
	
	//Dynamic size matrix of floats
	MatrixXf D;
	D.resize(3,3);
	
	//Set D as an identity matrix
	D.setIdentity();
	
	cout << "Matrix D:" << "\n" << D << "\n";
	
	//Multiplication of matrix and matrix
	MatrixXf E = A * D;
	
	cout << "E = A * D:" << "\n" << E << "\n";
	
	return 0;
}
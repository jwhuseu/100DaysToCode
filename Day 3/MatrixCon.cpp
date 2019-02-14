//This program is just to test out basics of array calling
//used within classes. This will also try my hand at more
//object-orientated programming (OOP) design.

#include <iostream>
using namespace std;

class TestMatrix
{
	private: 
	int tm_MatrixSize; 
	int *tm_MatrixA;
	int *tm_MatrixB;
	
	public:
	int *MatrixC;
	
	TestMatrix(int tm_MatrixSize = 5);
	~TestMatrix(void);
	
	void MatrixGeneration(int *tm_MatrixA, int *tm_MatrixB, int tm_MatrixSize);
	void MatrixAddition(int *tm_MatrixA, int *tm_MatrixB, int tm_MatrixSize);	
};

int main()
{
	TestMatrix Matrix;
	
	Matrix;
	
	for (int n = 0; n < 5; n++)
	{
		cout << Matrix.MatrixC[n] << endl;
		
	}
	return 0;
}

TestMatrix::TestMatrix(int tm_MatrixSize)
{
	cout << "Please indicate what size matrix you wish to solve:" << endl;
	cin >> tm_MatrixSize;
	
	tm_MatrixA = new int[tm_MatrixSize];
	tm_MatrixB = new int[tm_MatrixSize];
	MatrixC = new int[tm_MatrixSize];
	
	MatrixGeneration(tm_MatrixA, tm_MatrixB, tm_MatrixSize);
	MatrixAddition(tm_MatrixA, tm_MatrixB, tm_MatrixSize);
}

TestMatrix::~TestMatrix(void)
{
	delete[] tm_MatrixA;
	delete[] tm_MatrixB;
	delete[] MatrixC;
}

void TestMatrix::MatrixGeneration(int *tm_MatrixA, int *tm_MatrixB, int tm_MatrixSize)
{
	//Basic test for MatrixA
	for (int n = 0; n < tm_MatrixSize; n++)
	{
		tm_MatrixA[n] = 5;
	}
	
	//Basic test for MatrixB
	for (int n = 0; n < tm_MatrixSize; n++)
	{
		tm_MatrixB[n] = 2;
	}
}

void TestMatrix::MatrixAddition(int *tm_MatrixA, int *tm_MatrixB, int tm_MatrixSize)
{
	for (int n = 0; n < tm_MatrixSize; n++)
	{
		MatrixC[n] = tm_MatrixA[n] + tm_MatrixB[n];
	}
}
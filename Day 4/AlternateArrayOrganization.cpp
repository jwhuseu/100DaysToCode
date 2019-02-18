/*It was recommended to declare the 2D arrays 
  as a single array. So this will be testing on how 
  to operate on a single array (like how it is stored in
  memory) then output.*/
  
#include <iostream>
using namespace std;

int main()
{
	int MatrixRow = 10;
	int MatrixColumn = 10;
	
	int Matrix2D[MatrixRow*MatrixColumn] = {};
	
	int UpperDiagonal = 3;
	int MiddleDiagonal = 2;
	int LowerDiagonal = 1;
	int RemainderDiagonal = 0;
	
	//Array fill with zeros (Idea for this was to make sure if the 
	//data type of the array changes, it will always be zero.)
	
	for (int n = 0; n < MatrixRow * MatrixColumn; n++)
	{
		Matrix2D[n] = RemainderDiagonal;
	}
	
	//Matrix generation for the diagonals
	for (int n = 0; n < MatrixRow * MatrixColumn; n++)
	{
		if (n == 0 || n%(MatrixRow+1) == 0)
		{
			Matrix2D[n] = MiddleDiagonal;
		}
		
		if (n == 1 || n%(MatrixRow+1) == 1)
		{
			Matrix2D[n] = UpperDiagonal;
		}
		
		if (n != 0 && n%(MatrixRow+1) == 0)
		{
			Matrix2D[n - 1] = LowerDiagonal;
		}
	}
	
	//Array output
	for (int n = 0; n < MatrixRow * MatrixColumn; n++)
	{
		if (n%MatrixRow == 0 && n != 0)
		{
			cout << endl;
		}
		
		cout << Matrix2D[n] << " ";
		
		if (n == MatrixRow * MatrixColumn - 1)
		{
			cout << endl;
		}
	}
	
	return 0;
}
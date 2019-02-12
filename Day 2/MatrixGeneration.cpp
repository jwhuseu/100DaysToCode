//This basic program will create a 2D array to represent a basic triangular matrix.
//The goal is reduce amount of for loops and if else used and instead use of just if statements.

#include <iostream>
using namespace std;

int main()
{
	//Basics for the matrix size.
	int RowSize = 5;
	int ColumnSize = 5;
	
	int TriangularMatrix[RowSize][ColumnSize] = {};
	
	//Coefficients to test the matrix generation
	int Diagonal = 3;
	int UpperDiagonal = 2;
	int LowerDiagonal = 1;
	int RestofMatrix = 0;
	
	//Matrix generation.
	for (int i = 0; i < RowSize; i++)
	{
		for (int j = 0; j < ColumnSize; j++)
		{
			if (j == i)
			{
				TriangularMatrix[i][j] = Diagonal;
			}
			
			if (j == i + 1)
			{
				TriangularMatrix[i][j] = UpperDiagonal;
			}
			
 			if (j == i - 1)
			{
				TriangularMatrix[i][j] = LowerDiagonal;
			} 
			
 			if (j != i && j != i + 1 && j != i - 1)
			{
				TriangularMatrix[i][j] = RestofMatrix;
			} 
		}
	}
	
	//Matrix Output
	
	for (int i = 0; i < RowSize; i++)
	{
		for (int j = 0; j < ColumnSize; j++)
		{
			cout << TriangularMatrix[i][j] << " ";
		}
		
		cout << endl;
	}
	
	
	return 0;
}
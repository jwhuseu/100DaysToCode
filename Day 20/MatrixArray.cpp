/* This code is a basic test of trying
 * to treat a 1D array as a matrix. This 
 * will be a basic test on outputting
 * the contents of the array and generating  
 * an identity matrix.
 */
 
#include <iostream>
using namespace std;

int main()
{
	int Row = 5;
	int Column = 5;
	int TotalMatrixSize = Row * Column;
	int Array[TotalMatrixSize] = {};
	
	//Basic matrix fill with zeros.
	for (int i = 0; i < TotalMatrixSize; i++)
	{
		Array[i] = 0;
 	}
	
	//Basic matrix output_iterator
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Column; j++)
		{
			cout << Array[i * Column + j] << " ";
		}
		
		cout << "\n";
	}
	
	//Identity matrix generation
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Column; j++)
		{
			if (j == i)
			{
				Array[i * Column + j] = 1;
			}
			
			if (j != i)
			{
				Array[i * Column + j] = 0;
			}
		}
	}
	
	//Identity matrix output
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Column; j++)
		{
			cout << Array[i * Column + j] << " ";
		}
		
		cout << "\n";
	}
	
	return 0;
}
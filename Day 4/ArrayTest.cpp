/* This program will be to test about 
   passing pointer arrays to functions
   and see how the pointers are effected 
   by the programs.*/
   
#include <iostream>
using namespace std;

void ArrayModifier(int InsertArray[], int ArrayLength);

int main()
{
	//Generated test array and pointer to said array.
	int ArrayLength = 10;
	int ArrayTest = 5;
	int *GeneratedArray = new int[ArrayLength];
	
	cout << "This array will be output and called array1: " << endl;
	
	//Modify the array first.
	for (int n = 0; n < ArrayLength; n++)
	{
		GeneratedArray[n] = ArrayTest;
	}
	
	//Output the array before modification
	
	for (int n = 0; n < ArrayLength; n++)
	{
		cout << GeneratedArray[n] << " ";
	}
	
	cout << endl;
	
	//Testing the modification of the pointer array. 
	
	ArrayModifier(GeneratedArray, ArrayLength);
	
	cout << "This is the modifed array: " << endl;
	
	for (int n = 0; n < ArrayLength; n++)
	{
		if (GeneratedArray[n] == ArrayTest)
		{
			cout << "The array was not modified." << endl;
		}
		
		if (GeneratedArray[n] != ArrayTest)
		{
			cout << GeneratedArray[n] << " ";
		}
	}
	
	cout << endl;
	
	return 0;
}

void ArrayModifier(int InsertArray[], int ArrayLength)
{
	for (int n = 0; n < ArrayLength; n++)
	{
		InsertArray[n] += 5;
	}
}
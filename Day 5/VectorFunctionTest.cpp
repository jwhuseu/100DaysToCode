/*Basic test that will involve passing vectors to 
  functions as either a pointer or just the vector 
  itself.*/
  
#include <iostream>
#include <vector>
using namespace std;

void VectorClassModifier(vector<int> &TestVector);

int main()
{
	vector<int> Test;
	
	VectorClassModifier(Test);
	
	//Test output for either of the values.
	
	for (int n = 0; n < 10; n++)
	{
		//cout << "The test value of Test1 is: " << Test1[n] << endl;
		cout << "The test value of Test2 is: " << Test[n] << endl;
	}
	return 0;
}

void VectorClassModifier(vector<int> &TestVector)
{
	for (int n = 0; n < 10; n++)
	{
		TestVector.push_back(n);
	}
}
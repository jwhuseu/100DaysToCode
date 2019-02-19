/* This code is just an example of the use 
   of vectors in C++. Nothing too interesting, 
   just the deployment of a basic 1D vector and 
   some basic modifications.
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	//Basic vector argument structure. 
	//template <class T, class Alloc = allocator<T>> class vector;
	
	int VectorSize = 5;
	vector<int> v;
	
	//Input values into the vector
	for (int n = 0; n < VectorSize; n++)
	{
		v.push_back(n);
	}
	
	//Displace the values of the vector
	for (int n = 0; n < VectorSize; n++)
	{
		cout << v[n] << endl;
	}
	
	//Display the total size of the vector 
	
	cout << "The current size of the vector v is: " << v.size() << endl;
	
	//Now we are clearing the vector of all values.
	
	v.clear();
	
	return 0;
}
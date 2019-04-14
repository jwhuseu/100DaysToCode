/* This code is intended to test how to
 * pass a class or struct object as an
 * argument to a function.
 */
 
#include <iostream>
using namespace std;

struct Object
{
	int TestOne = 1;
	int TestTwo = 2;
	int TestThree = 3;
};

void ObjectOutput(Object &Testing);

int main()
{
	Object Test;
	
	ObjectOutput(Test);
	return 0;
}

void ObjectOutput(Object &Testing)
{
	cout << Testing.TestOne << "\n";
	cout << Testing.TestTwo << "\n";
	cout << Testing.TestThree << "\n";
}
/* This is a basic program that will deal with 
 * basic pomymorphism and class inheritance concepts
 * that I recently read up on and hope to use
 * to improve my current projects.
 */
 
#include <iostream>
using namespace std;

class Test
{
	public:
	int TestMethod(int a, int b, int c)
	{
		return a + b + c;
	}
};

class Subtraction: public Test
{
	public:
	int TestMethod(int a, int b, int c)
	{
		return a - b -  c;
	}
};

class Multiplication:  public Test
{
	public:
	int TestMethod(int a, int b, int c)
	{
		return a * b * c;
	}
};

//Yeah, this didn't work. 
//Forgot about the part where objects and methods for classes are declared at compile time.
//Back to the drawing board. 
int main()
{
	int a = 3;
	int b = 2;
	int c = 1;
	
	int Guess = 6;
	Test Object;
	
	if (Guess == 4)
	{
		Test Object;
	}
	
	if (Guess == 5)
	{
		Subtraction Object;
	}
	
	if (Guess == 6)
	{
		Multiplication Object;
	}
	
	cout << Object.TestMethod(a, b, c) << "\n";
	
	return 0;
}
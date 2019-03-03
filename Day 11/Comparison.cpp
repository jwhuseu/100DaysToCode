#include <iostream>
#include <string>
using namespace std;

string Comparison(int a, int b)
{
	return a > b ?  "No" : "Yes";
}

int main()
{
	int a = 10;
	int b = 20;
	
	cout << Comparison(a, b) << "\n";
	return 0;
}
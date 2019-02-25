#include <iostream>
using namespace std;

class Circle
{
	private:
	const double pi = 3.14;
	
	public:
	double RadiusInput();
	double AreaCalc(double radius);
	double CircumferenceCalc(double radius);
};
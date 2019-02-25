#include "Circle.hpp"
double Circle::RadiusInput()
{
	double radius;
	cout << "Please enter the radius you wish to calculate for." << endl;
	cin >> radius;
	
	return radius;
}
double Circle::AreaCalc(double radius)
{
	cout << "The area of the circle is: " << radius * radius * pi << endl;
}
double Circle::CircumferenceCalc(double radius)
{
	cout << "The circumference of the circle is: " << 2 * radius * pi << endl;
}
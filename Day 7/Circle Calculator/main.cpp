#include "Circle.hpp"

int main()
{
	Circle Circ;
	int test;
	
	test = Circ.RadiusInput();
	
	Circ.AreaCalc(test);
	Circ.CircumferenceCalc(test);
	
	return 0;
}
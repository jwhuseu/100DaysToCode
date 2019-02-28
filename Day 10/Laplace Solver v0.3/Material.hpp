#ifndef MATERIAL
#define MATERIAL

struct Material
{
	double DiffusionCoefficient;
	
	double MaterialDefinition(double DiffusionCoefficient = 1);
};

#endif
#ifndef MATERIALPROPERTIES
#define MATERIALPROPERTIES

struct MaterialProperties
{
	double ThermalConductivity;
	
	MaterialProperties(double ThermalProperty);
	~MaterialProperties();
};

MaterialProperties:MaterialProperties(double ThermalProperty)
{
	ThermalConductivity = ThermalProperty;
}

MaterialProperties::~MaterialProperties()
{
}
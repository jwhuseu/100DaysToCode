#ifndef DISC_GEOMETRY
#define DISC_GEOMETRY

struct Geometry 
{
	double Length;
	double Height;
	
	double GeometryDefinition(double DefinedLength = 1, double DefinedHeight = 1);
};

struct Discretization
{
	double NodeX;
	double NodeY;
	double GhostNodeX;
	double GhostNodeY;
	double DeltaX;
	double DeltaY;
	
	double DiscretizationDefinition(double NodeX = 1, double NodeY = 1, double GhostNodeX = 1, double GhostNodeY = 1,
									double DeltaX = 1, double DeltaY = 1);
};

#endif
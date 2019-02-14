#ifndef GEOMETRYDEFINITION
#define GEOMETRYDEFINITION

struct GeometryDefinition
{
	//Default Geometry Dimensions
	double height;
	double length;
	
	//Default discretization information
	int xInteriorNodes;
	int yInteriorNodes;
	int xGhostCells;
	int yGhostCells;
	
	double xGridSpacing;
	double yGridSpacing;
	
	//Basic constructors that will accept the values from
	//main and that translate that to the variables stored 
	//here.
	
	GeometryDefinition(double TakenHeight, double TakenLength, 
						int xInterior, int yInteriorNodes, int xGhost, int yGhost);
	~GeometryDefinition();
};

GeometryDefinition::GeometryDefinition(double TakenHeight, double TakenLength, 
						int xInterior, int yInterior, int xGhost, int yGhost)
{
	height = TakenHeight;
	length = TakenLength;
	xInteriorNodes = xInterior;
	yInteriorNodes = yInterior;
	xGhostCells = xGhost;
	yGhostCells = yGhost;
	
	xGridSpacing = length / (xInteriorNodes - 1);
	yGridSpacing = height / (yInteriorNodes - 1);
}

GeometryDefinition::~GeometryDefinition()
{
}
						

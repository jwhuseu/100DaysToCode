#include "Disc_Geometry.hpp"

double Geometry::GeometryDefinition(double DefinedLength, double DefinedHeight)
{
	Length = DefinedLength;
	Height = DefinedHeight;
}

double Discretization::DiscretizationDefinition(double DefinedNodeX, double DefinedNodeY, double DefinedGhostNodeX, double DefinedGhostNodeY,
									double DefinedDeltaX, double DefinedDeltaY)
{
	NodeX = DefinedNodeX;
	NodeY = DefinedNodeY;
	GhostNodeX = DefinedGhostNodeX;
	GhostNodeY = DefinedGhostNodeY;
	DeltaX = DefinedDeltaX;
	DeltaY = DefinedDeltaY;
}
#ifndef BOUNDARYCONDITIONS
#define BOUNDARYCONDITIONS

class BoundaryConditions
{
	private:
	double TopBoundary;
	double BottomBoundary;
	double LeftBoundary;
	double RightBoundary;
	
	public:
	void DirichletBC();
	void NeumannBC();
	
	BoundaryConditions();
	~BoundaryConditions();
	
};

void BoundaryConditions::DirichletBC()
{
}

void BoundaryConditions::NeumannBC()
{
}

BoundaryConditions::BoundaryConditions()
{
}

BoundaryConditions::~BoundaryConditions()
{
}
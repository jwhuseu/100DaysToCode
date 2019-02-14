#ifndef INITIALCONDITIONS
#define INITIALCONDITIONS

class InitialConditions
{
	private:
	double SourceValue;
	double FieldValue;
	
	public:
	void PointSourceGeneration();
	void FieldInitialization();
	
	InitialConditions();
	~InitialConditions();
};

void InitialConditions::PointSourceGeneration()
{
}

void InitialConditions::FieldInitialization()
{
}
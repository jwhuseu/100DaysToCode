/* This section of code will contain the 
 * solution container for the Burgers 
 * equation and as well the base 
 * functions that will used to declare the 
 * initialization conditions.
 */
 
#ifndef SOLUTIONCONTAINER
#define SOLUTIONCONTAINER

class SolutionContainer
{
	public:
	double ResidualVector[];
	double SolutionVector[];
	
	//Class functions that match the initial condition tests
	void ShockTubeInitial(int NodeX, double LeftShock, double RightShock);
	void WaveInitial(int NodeX, double PeakWave, double LowWave);
	
	//Class constructor and deconstructor
	SolutionContainer(int NodeX);
	~SolutionContainer();
};


#endif
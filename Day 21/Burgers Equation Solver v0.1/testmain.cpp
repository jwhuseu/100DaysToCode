/* This is intended as test main for the code
 * that solves for the Burgers' equation.
 */

#include <iostream>
#include "ProblemDefinition.hpp"
#include "SolutionContainer.hpp"
#include "FluxScheme.hpp"
using namespace std;

void ProblemDefinitionOutput(ProblemDefinition &Terms);

int main()
{
	ProblemDefinition Problem;
	
	ProblemDefinitionOutput(Problem);
	
	return 0;
}

void ProblemDefinitionOutput(ProblemDefinition &Terms)
{
	cout << Terms.Length << "\n";
	cout << Terms.TotalTime << "\n";
	cout << Terms.NodeX << "\n";
	cout << Terms.TimeStep << "\n";
	cout << Terms.DeltaX << "\n";
	cout << Terms.DeltaTime << "\n";
	cout << Terms.LeftShock << "\n";
	cout << Terms.RightShock << "\n";
	cout << Terms.InitialPeak << "\n";
	cout << Terms.InitialLow << "\n";
	cout << Terms.LeftBoundaryOne << "\n";
	cout << Terms.RightBoundaryOne << "\n";
	cout << Terms.LeftBoundaryOne << "\n";
	cout << Terms.RightBoundaryTwo << "\n";
}
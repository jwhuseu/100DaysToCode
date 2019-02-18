/* This program will be used to create a solution
   for the 1D advection equation using the Crank-
   Nicolson method. This will be an attempt to write 
   the solver steps all by hand. There might be issue 
   with some mathematical operaations. If there are issues
   then the use of libraries will be considered.   */
   
   //The discretization is followed from this:
   //https://scicomp.stackexchange.com/questions/7399/how-to-discretize-the-advection-equation-using-the-crank-nicolson-method
   
//Current Version Last Modified: 2 - 18 - 2019
//Known Issues: So far none
//Planned Changes. Going to refactor the code to work with vectors or 1D arrays instead of a bunch
//of 2D array of pointers

#include <iostream>
using namespace std;

//Function prototypes 
void LHS_MatrixGeneration(double Array[][], int xNodes, double Beta, double LeadingCoefficient);
void RHS_MatrixGeneration(double Array[][], int xNodes, double Beta, double LeadingCoefficient);
void LHS_VectorGeneration(double Vector[], int xNodes);
void RHS_VectorGeneration(double Vector[], int xNodes, int BoundaryConditionA, int BoundaryConditionB);

void VectorInitialization();
void VectorBoundaryConditions();
void MatrixInversion();
void CoefficientMatrix();
void GaussianElimination();

int main()
{
	//Problem variable declarations
	double Length = 1.0;
	double Time = 2.0;
	double WaveSpeed = 2.0;
	int const xNodes = 50;
	int TimeSteps = 30;
	double Beta = 0.5;
	
	//Discretization
	double deltaX = Length / (1 - xNodes);
	double deltaTime = Time / (1 - TimeSteps);
	double LeadingCoefficient = WaveSpeed * deltaTime / deltaX / 2.0;
	
	//Boundary Condition variables
	
	//Initial Condition variables 

	//Matrix and Vector declaration, with additional declared
	//matrices and vectors which might be needed for later use
	//but might not be needed and will be removed when the
	//program is finished. 
	
	//Known issues here: Need to make the xNodes a constant (No idea why at the moment, will look into later)
	//Cannot declare 2D array as [xNodes][xNodes]. Need to look into that as well.
	
	double **LHS_Matrix = new double*[xNodes];
	double **RHS_Matrix = new double*[xNodes];
	double **LHS_MatrixCopy = new double*[xNodes];
	double **RHS_MatrixCopy = new double*[xNodes];
	
	double *LHS_Vector = new double[xNodes];
	double *RHS_Vector = new double[xNodes];
	double *LHS_VectorCopy = new double[xNodes];
	double *RHS_VectorCopy = new double[xNodes];
	
	//Finalizing the pointers for the 2D array declaration 
	for (int n = 0; n < xNodes; n++)
	{
		LHS_Matrix[n] = new double[xNodes];
		RHS_Matrix[n] = new double[xNodes];
		LHS_MatrixCopy[n] = new double[xNodes];
		RHS_MatrixCopy[n] = new double[xNodes];
	}
	
	//Pointer to array deletion.
	
	for (int n = 0; n < xNodes; n++)
	{	
		delete[] LHS_Matrix[n];
		delete[] RHS_Matrix[n];
		delete[] LHS_MatrixCopy[n];
		delete[] RHS_MatrixCopy[n];
	}
	
	delete[] LHS_Matrix;
	delete[] RHS_Matrix;
	delete[] LHS_MatrixCopy;
	delete[] RHS_MatrixCopy;
	
	delete[] LHS_Vector;
	delete[] RHS_Vector;
	delete[] LHS_VectorCopy;
	delete[] RHS_VectorCopy;
	
	
	return 0;
}
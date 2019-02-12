#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
// Title: FVM Matrix Solver
// Problem is using a derived FVM discretization to solve 1D Heat Conduction problem

float **matrixCon(int nx, float Area, float Length, int diffCoeff, float dx);
float *matrixSolver(float **matrix, int nx, float Ta, float Tb, float Area, float Length, int diffCoeff, float dx);
float matrixOutput(float **results, int nx);
float vectorOutput(float *vector, int nx, float Ta, float Tb, float Length);

int main()
{
	int diffCoeff, nx;
	float Ta, Tb, Area, Length, dx, **temp1, **temp2, *tempVector;
	
	//Geometry Conditions: SI Units
	nx = 5;
	Area = 0.01;
	Length = 0.5;
	dx = Length/nx;
	diffCoeff = 1000;
	
	//Boundary conditions
	Ta = 100;
	Tb = 500;
	
	//solver test region
	temp1 = matrixCon(nx, Area, Length, diffCoeff, dx);
	tempVector = matrixSolver(temp1, nx, Ta, Tb, Area, Length, diffCoeff, dx);
	matrixOutput(temp1, nx);
	vectorOutput(tempVector, nx, Ta, Tb, Length);
	
	return 0;
}

float **matrixCon(int nx, float Area, float Length, int diffCoeff, float dx)
{
	int i, j;
	
	float **tempMatrix = new float*[nx];
	
	for (j = 0; j < nx; j++)
	{
		tempMatrix[j] = new float[nx];
	}
	
	//Diagonal generation
	
	for (j = 0; j < nx; j++)
	{
		for (i = 0; i < nx; i++)
		{
			if ((i == 0 ) || (j == 0))
			{
				tempMatrix[j][i] = (diffCoeff * Area / dx) + (2* diffCoeff * Area / dx);
			}
			else if ((i < (nx - 1)) || j < ((nx - 1)))
			{
				tempMatrix[j][i] = (diffCoeff * Area / dx) + (diffCoeff * Area / dx);
			}
			else if ((i == (nx - 1)) || j == ((nx - 1)))
			{
				tempMatrix[j][i] = (diffCoeff * Area / dx) + (2* diffCoeff * Area / dx);
			}
		}
	}
	
	//Upper matrix
	
	for (j = 0; j < nx; j++)
	{
		for (i = 0; i < nx; i++)
		{
			if (i == j+1)
			{
				tempMatrix[j][i] = -diffCoeff * Area / dx;
			}
			else if (i > j)
			{
				tempMatrix[j][i] = 0;
			}
		}
	}
	
	//Lower matrix
	
	for (j = 1; j < nx; j++)
	{
		for (i = 0; i < nx; i++)
		{
			if (i == j - 1)
			{
				tempMatrix[j][i] = -diffCoeff * Area / dx;
			}
			else if (i < j)
			{
				tempMatrix[j][i] = 0;
			}
		}
	}
	
	return tempMatrix;
}

float *matrixSolver(float **matrix, int nx, float Ta, float Tb, float Area, float Length, int diffCoeff, float dx)
{
	int i, j;
	double temp;
	float *vector = new float[nx];
	float newMatrix[nx][nx+1] = {};
	
	//Sets the pointer array to a new local array
	for (j = 0; j < nx; j++)
	{
		for (i = 0; i < nx; i++)
		{
			newMatrix[j][i] = matrix[j][i];
		}
	}
	
	//Created augmented matrix
	for (j = 0; j < nx; j++)
	{
		if (j == 0)
		{
		newMatrix[j][nx] = 2* Ta * diffCoeff * Area / dx;
		}
		else if (j = nx-1)
		{
		newMatrix[j][nx] = 2 * Tb * diffCoeff * Area / dx;
		}			
		else
		{
			newMatrix[j][nx] = 0;
		}
	}
	
	//Guassian Elimination (Used the solution approach in this code: http://www.bragitoff.com/2015/09/c-program-for-gauss-elimination-for-solving-a-system-of-linear-equations/)
	
	for (i = 0; i<nx-1; i++)
	{
		for (int k = i+1; k < nx; k++)
		{
			temp = newMatrix[k][i]/newMatrix[i][i];
			for (j = 0; j <=nx; j++)
			{
				newMatrix[k][j] = newMatrix[k][j] - temp * newMatrix[i][j];
			}
		}
	}
	
	for (i = nx -1; i>=0; i--)
	{
		vector[i] = newMatrix[i][nx];
		
		for (j = i+1; j<nx; j++)
		{
			if (j != i)
			{
				vector[i] = vector[i] - newMatrix[i][j]*vector[j];
			}
		}
		vector[i] = vector[i] / newMatrix[i][i];
	}

	return vector;
}

float matrixOutput(float **matrix, int nx)
{
	int i, j;
	
	cout << "The coefficient matrix is the following:" << endl;
	for (j = 0; j < nx; j++)
	{
		for (i = 0; i < nx; i++)
		{
			cout << setw(5) << matrix[j][i]; 
		}
		cout << "\n";
	}
}

float vectorOutput(float *vector, int nx, float Ta, float Tb, float Length)
{
	ofstream a_file ("out.dat");
	int j;
	float x, dx;
	dx = Length / (nx+1);
	x = 0;
	
	cout << "The full range of temperatures are given as:" << endl;
	cout << Ta << endl;
	
	a_file << "# output.dat\n";
	a_file << "# X  Y\n";
	a_file << setw(4) << x << setw(4)  << Ta << endl;
	
	for (j =0; j < nx; j++)
	{
		cout << vector[j] << endl;
		x = x + dx;
		
		a_file << setw(4) << setprecision(3) << x << setw(4) << vector[j] << endl;
		
	}

	cout << Tb << endl;
	a_file << setw(4) << Length << setw(4) << Tb << endl;
}
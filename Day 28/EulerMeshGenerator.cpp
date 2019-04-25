/* Basic code that creates a 1D
 * "mesh" file for me to prototype
 * for my Euler equation solver code.
 * This is version v0.1.
 */
 
//General mesh format [#Node | x-Coordinate | Density | Velocity | Pressure]
 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void ShockTubeInitialization(double Array[], int NodeCount, string ShockTube);
void RegularGrid(double Array[], double Length, double NodeCount);

int main()
{
	//Basic file declaration
	ofstream OutFile;
	OutFile.open("Mesh.txt");
	
	//Problem definitition and "other information"
	double Length = 1.0;
	int NodeCount = 50;
	double MeshArray[5*NodeCount] = {};
	string ShockTube = "ClassicSod";
	string GridType = "Regular";
	
	//Basic code prototyping
	RegularGrid(MeshArray, Length, NodeCount);
	ShockTubeInitialization(MeshArray, NodeCount, ShockTube);
	
	//File output
	OutFile << "#1D Compressible Euler Mesh File" << "\n"
			<< ShockTube << "\n"
			<< NodeCount << "\n";
			
	for (int n = 0; n < NodeCount; n++)
	{
		OutFile << MeshArray[n*5] << " "
				<< MeshArray[n*5+1] << " "
				<< MeshArray[n*5+2] << " "
				<< MeshArray[n*5+3] << " "
				<< MeshArray[n*5+4] << " "
				<< "\n";
	}
	
	//Finalized operations
	OutFile.close();
	
	return 0; 
}

void ShockTubeInitialization(double Array[], int NodeCount, string ShockTube)
{
	if (ShockTube == "ClassicSod")
	{
		for (int n = 0; n < NodeCount; n++)
		{
			if (n <= 0.5 * NodeCount)
			{
				Array[n*5+2] = 1.0; 
				Array[n*5+3] = 0.0;
				Array[n*5+4] = 1.0;
			}
			else
			{
				Array[n*5+2] = 0.125; 
				Array[n*5+3] = 0.0;
				Array[n*5+4] = 0.1;
			}
		}
	}
}

void RegularGrid(double Array[], double Length, double NodeCount)
{
	double DeltaX = Length/ (NodeCount - 1);
	double NodeNumber = 0;
	
	for (int n = 0; n < NodeCount; n++)
	{
		if (n == 0)
		{
			NodeNumber = 0;
		}
		
		if (n != 0)
		{
			NodeNumber += DeltaX;
		}
		
		Array[n*5] = n;
		Array[n*5 + 1] = NodeNumber;
	}
}
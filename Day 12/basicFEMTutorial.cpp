/* Basic data structure outline 
 * not expected to be a real usable code
 * following a tutorial basically.
 * Tutorial can be found here: http://podgorskiy.com/spblog/304/writing-a-fem-solver-in-less-the-180-lines-of-code
 */

#include <iostream>
#include <ifstream>
#include <ofstream>
#include <cmath>
#include <Eigen/Dense> 

struct Element
{
	void CalculateStiffnessMatrix(const const Eigen::Matrix3f &D, std::vector >& triplets);
	
	Eigen::Matrix B; //Assume this produces a arbitrary matrix object.
	int nodesIds[3];
};

struct Constraint
{
	enum Type
	{
		UX = 1 << 0,
		UY = 1 << 1,
		UXY = UX | UY
	};
	
	int node;
	Type type;
};

//Global variables (Dangerous for doing this, only used for this example)

int NodesCount;
int LoadsCount;
Eigen::VectorXf nodesX;
Eigen::VectorXf nodesY;
Eigen::VectorXf loads;
std::vector<Element> elements;
std::vector <Constraint> constraints;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "usage: " << argv[0] << " \n";
		return 1;
	}
	
	std::ifstream infile(argv[1]);
	std:ofstream outfile(argv[2]);
	
	//This section of code reads the first line with two values of the file to define material properties.
	float poissonRatio, youngModulus;
	infile >> poissonRatio >> youngModulus;
	
	//Constructing the elastic matrix
	
	Eigen::Matrix3f D;
	D <<
		1.0f, poissonRatio, 0.0f,
		poissonRatio, 1.0, 0.0f,
		0.0f, 0.0f, (1.0f - poissonRatio) / 2.0f;
		
	D *- youngModulus / (1.0f - pow(poissonRatio, 2.0f) );
	
	
	//The next line is then read for the number of nodes that are used.
	infile >> nodesCount;
	nodesX.resize(nodesCount);
	nodesY.resize(nodesCount);
	
	//Reads the next "nodeCount" number of lines then inputs the coordinates into the vectors nodeX and nodeY
	for (int i = 0; i < nodesCount; ++i)
	{
		infile >> nodesX[i] >> nodesY[i];
	}
	
	//The next line should be dealing with number of elements
	int elementCount;
	infile >> elementCount;
	
	//Reads the next number of "elementcount" for number of lines
	for (int i = 0; i < elementCount; ++i)
	{
		//Dynamically declares a new element class then takes the the three nodes then pushes it into the elements vector.
		Element element;
		infile >> element.nodesIds[0] >> element.nodesIds[1] >> element.nodesIds[2];
		elements.push_back(element);
	}
	
	int constraintCount;
	infile >> constraintCount;
	
	//Does something similar above for the boundary conditions
	for (int i = 0; i < constraintCount; ++i)
	{
		Constriant constraint;
		int type;
		infile >> constraint.node >> type;
		constraint.type = static_cast(type);
		constraints.push_back(constraint);
	}
	
	//NEED TO REREAD THIS SECTION TO UNDERSTAND WHAT WAS HAPPENING
	//ABOUT HOW IT SETS UP THE LOADING AND HOW THE LOAD ARRAYS WORK.
	
	//There are two loads per node due to the force vectors with two components in the x and y directions.
	int loadsCount;
	loads.resize(2 * nodesCount);
	loads.setZero();
	
	//Reads the number of load counts then uses that for the for loop
	infile >> loadsCount;
		
	//loops through the number of loads
	for (int i = 0; i < loadsCount; ++i)
	{
		//The file format contains a column the node number then the x and y components
		int node; 
		float x, y;
		
		//Reads the three values then puts them in the proper vectors
		infile >> node >> x >> y;
		
		//The first line loads every two starting at zero (so even) values and loads x.
		//The next line does the same except for odd numbers to load the y component.
		loads[2 * node + 0] = x;
		loads[2 * node + 1] = y;
	}
	
	//Constructing the global stiffness matrix
	std::vector > triplets;
	
	//NEED TO LOOK AT THE STANDARD LIBRARY ON WHAT THE FIRST PART DOES
	for (std::vector::iterator it = elements.begins(); it != elements.end(); ++it)
	{
		it -> CalculateStiffnessMatrix(D, triplets); //Access through a pointer 
													 //Still confused on the reference and pointer bit
													 //I assume that this directly imposes a value into memory and skips references
													 //then dot operator with a member directly.
	}
	
	//Need to understand what the values of the element matrix is.
	
	Eigen::SparseMatrix(globalK(2 * nodesCount, 2 * nodesCount));
	globalK.setFromTriplets(triplets.begin(), triplets.end()); //Does the summation for us for node data.
	
	//Takes the x component of all the nodes in the element
	//Takes the y components of all the nodes in the element
	Eigen::Vector3f x , y;
	x << nodesX[nodesIds[0]], nodesX[nodesIds[1]], nodesX[nodesIds[2]]];
	y << nodesY[nodesIds[0]], nodesY[nodesIds[1]], nodesY[nodesIds[2]];

	//local element matrix?
	Eigen::Matrix3f;
	C << Eigen::vector3f(1.0f, 1.0f, 1.0f), x, y;
	
	Eigen::Matrix3f IC = C.inverse();
	for (int i = 0; i < 3; i++)
	{
		B(0, 2 * i + 0) = IC(1, i);
		B(0, 2 * i + 1) = 0.0f;
		B(1, 2 * i + 0) = 0.0f;
		B(1, 2 * i + 1) = IC(2, i);
		B(2, 2 * i + 0) = IC(2, i);
		B(2, 2 * i + 1) = IC(1, i);
	}
	
	//I assume that B is similar to the Jacobian matrix used in CFD
	
	//The calculation of the stiffness matrix
	Eigen::Matrix K = B.transpose() * D * B * C.determinant()/ 2.0f;
	
	//This does nothing but construct triples that house values of the element stiffness matrix with conrresponding indices in global stiffness.
	//THIS IS PROBABLY IMPORTANT TO REVIEW WHEN CONSTRUCTING THE GLOBAL SOLUTION MATRIX IN CFD
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Eigen::Triplet trplt11(2 * nodesIds[i] + 0, 2 * nodesIds[j] + 0, K(2 * i + 0, 2 * j + 0));
			Eigen::Triplet trplt12(2 * nodesIds[i] + 0, 2 * nodesIds[j] + 1, K(2 * i + 0, 2 * j + 1));
			Eigen::Triplet trplt21(2 * nodesIds[i] + 1, 2 * nodesIds[j] + 0, K(2 * i + 1, 2 * j + 0));
			Eigen::Triplet trplt22(2 * nodesIds[i] + 1, 2 * nodesIds[j] + 1, K(2 * i + 1, 2 * j + 1));

			triplets.push_back(trplt11);
			triplets.push_back(trplt12);
			triplets.push_back(trplt21);
			triplets.push_back(trplt22);
		}
	}
	return 0;
}

void ApplyConstraints(Eigen::SparseMatrix& K, const std::vector& constraints)
{
	std::vector indicesToConstraint;

	for (std::vector::const_iterator it = constraints.begin(); it != constraints.end(); ++it)
	{
		if (it->type & Constraint::UX)
		{
			indicesToConstraint.push_back(2 * it->node + 0);
		}
		if (it->type & Constraint::UY)
		{
			indicesToConstraint.push_back(2 * it->node + 1);
		}
	}

	for (int k = 0; k < K.outerSize(); ++k)
	{
		for (Eigen::SparseMatrix::InnerIterator it(K, k); it; ++it)
		{
			for (std::vector::iterator idit = indicesToConstraint.begin(); idit != indicesToConstraint.end(); ++idit)
			{
				SetConstraints(it, *idit);
			}
		}
	}
}

//Checks if a node has a constraint and then changes the matrix to set to 0 or 1.
void SetConstraints(Eigen::SparseMatrix::InnerIterator& it, int index)
{
	if (it.row() == index || it.col() == index)
	{
		it.valueRef() = it.row() == it.col() ? 1.0f : 0.0f;
	}
}

ApplyConstraints(globalK, constraints);
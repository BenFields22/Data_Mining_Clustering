/********************************************************
Author:Benjamin Fields
Date:11/22/2016
File: Source.cpp
Description:Program that implements Agglomerative Clustering algorithm
on a three dimensional data set related to crime rates and moons in
the solar system. The program creates a proximity matrix using 
euclidian distances and evaluates the distance between clusters using 
the group average approach. Each merge is tracked and written to 
a text file for analyis after running the program. Similarly the 
proximity matrix can be seen in an external .csv file. The program
terminates once all points have been merged into one cluster. 
*************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include "Point.h"
#include <iomanip>
#include "Cluster.h"
#include "Merge.h"
#include "Clustering.h"

/**************************************************************
Description: read in the data file to be used for program data.
Either reads in the crime data or moon data based on assigned 
boolean
*************************************************************/
void readInData(std::vector<double> &myData, bool moons) {
	std::ifstream inputFile;
	if(moons == 0)
		inputFile.open("CrimesData.txt");
	else 
		inputFile.open("MoonsData.txt");
	double value;
	if (inputFile) {
		while (inputFile >> value) {
			myData.push_back(value);
		}
		inputFile.close();
	}
	else {
		std::cout << "Could not open File!" << std::endl;
	}
}
/**************************************************************
Description:writes the proximity matrix to a .csv file for further
analysis and tracking after running program.
*************************************************************/
void writeToFile(double *Matrix,int num) {
	std::ofstream myFile;
	myFile.open("Results.csv");
	int index = 0;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			myFile << Matrix[index]<<",";
			index++;
		}
		myFile << "\n";
	}
	
	myFile.close();

}
/**************************************************************
Description:writes the final merge results that were captured in 
the program to an external text file for further analysis and tracking
*************************************************************/
void writeMergeResults(Merge *myMerges, int num) {
	std::ofstream myFile;
	myFile.open("MergeResults.txt");
	
	myFile << "Merge Results\n\n";
	for (int i = 0; i < num; i++) {
		myFile << "Merge " << i + 1 << std::endl;
		myFile << "Cluster 1 ID: " << myMerges[i].getCluster1ID() << "\n";
		myFile << "Cluster 2 ID: " << myMerges[i].getCluster2ID() << "\n";
		myFile << "Merge Value: " << myMerges[i].getMergeValue() << "\n\n";
	}
	
	myFile.close();
}
/**************************************************************
Description:simple function to print a vector for checking
*************************************************************/
void printVector(std::vector<double> &myData) {
	for (int i = 0; i < (int)myData.size(); i++) {
		std::cout << "Data point " << i + 1 << " : " << myData[i] << std::endl;
	}
}
/**************************************************************
Description:function that takes the data that was read into the 
program and assigns in to points based on a given number of dimensions
*************************************************************/
std::vector<Point> createPoints(std::vector<double> &myData, int NumDim) {
	int numData = myData.size();
	int numPoints = numData / NumDim;
	std::vector<Point> myPoints;
	for (int i = 0; i < numPoints; i++) {
		Point next(myData[i], myData[i + numPoints], myData[i + 2 * numPoints],i+1);
		myPoints.push_back(next);
	}
	return myPoints;
}
/**************************************************************
Description:simple function to print the values of the points
for checking.
*************************************************************/
void printPoints(std::vector<Point> &myPoints) {
	for (int i = 0; i < (int)myPoints.size(); i++) {
		std::cout << myPoints[i].printPoint() << std::endl;
	}
}
/**************************************************************
Description:Function that calcualtes the proximity matrix for 
the given initial data points. The values use the euclidean distance
and outputs the results to the console as well as an array to store the
matrix for further use later in the program
*************************************************************/
double* ProximityMatrix(std::vector<Point> myPoints) {
	int numPoints = myPoints.size();
	double *myMatrix = new double[numPoints * numPoints];
	int index = 0;
	int spaces = 10;
	std::cout << std::left << std::setw(spaces+1)<<"   ";
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	for (int i = 0; i < (int)myPoints.size(); i++) {
		std::cout <<std::right<<std::setw(spaces)<< "Point " << i + 1 << " |";
	}
	std::cout << "\n";
	for (int i = 0; i < (int)myPoints.size(); i++) {
		std::cout <<std::left<<std::setw(spaces)<< "Point " << i + 1 << " | ";
		for (int j = 0; j < (int)myPoints.size(); j++) {
			std::cout <<std::right<<std::setw(spaces)<< myPoints[i].EuclidianDist(myPoints[j])<<" | ";
			myMatrix[index] = myPoints[i].EuclidianDist(myPoints[j]);
			index++;
		}
		std::cout << "\n";
	}
	return myMatrix;
}

/**************************************************************
Description:the main entry point of the program. This function controls
the execution of each step: 
	read in data
	organize data
	create proximity matrix
	track merging of clusters
	report results
*************************************************************/
int main(int argc, char **argv) {
	bool moons = 0;//boolean for determining which data set to use

	std::vector<double> myData;//initial vector to hold data

	readInData(myData, moons);
	printVector(myData);//checking line

	//create the initial point data structures for use in program
	std::vector<Point> myPoints = createPoints(myData, 3);

	printPoints(myPoints);//checking line
	double *myMatrix = ProximityMatrix(myPoints);//create proximity matrix
	writeToFile(myMatrix, myPoints.size());
	std::cout<<"\n";
	int numPoints = myPoints.size();

	//create initial cluster data structures with points
	Cluster *myClusters = new Cluster[numPoints];
	for (int i = 0; i < numPoints; i++) {
		myClusters[i].AddPoint(myPoints[i]);
		myClusters[i].setId(std::to_string(i + 1));
	}

	//check clusters
	for (int i = 0; i < numPoints; i++) {
		myClusters[i].printCluster();
	}

	//organize the data into a clustering data structure for easy data management
	Clustering myClustering;
	for (int i = 0; i < numPoints; i++) {
		myClustering.addCluster(myClusters[i]);
	}

	//create merge data structures for easy tracking of results in each iteration
	Merge *myMerges = new Merge[numPoints - 1];
	for (int i = 0; i < numPoints - 1; i++) {
		Merge nextMerge = myClustering.calulateSmallestandMerge();
		myMerges[i] = nextMerge;
	}

	//check results in console
	std::cout << "\n\nMerge Results\n\n";
	for (int i = 0; i < numPoints - 1; i++) {
		std::cout << "Merge " << i + 1 << std::endl;
		myMerges[i].printMerge();
	}

	//output results to test file
	writeMergeResults(myMerges, numPoints - 1);

	system("PAUSE");
	return 0;
}
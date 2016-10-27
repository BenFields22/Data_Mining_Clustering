/****************************************************************************************************************
Author: Benjamin Fields
	file :data set implementation file for functions
	Description :contains functions to act on data set
************************************************************************************************************** */
#include "DataSet.h"
#include<stdio.h>

//constructor
DataSet::DataSet(Point *array, int size) {
	mySet = new Point[size];
	for (int i = 0; i < size; i++) {
		mySet[i] = array[i];
	}
}
//print points
void DataSet::PrintSet() {
	for (int i = 0; i < 400; ++i) {
		printf("Set Point %d: X = %.2f  Y = %.2f\n", i + 1, mySet[i].getX(), mySet[i].getY());
	}
}

//get max value from a
float DataSet::getMaxX() {
	float largest = mySet[0].getX();
	for (int i = 0; i < 400; i++)
	{
		if (mySet[i].getX() > largest) {
			largest = mySet[i].getX();
		}
	}
	return largest;
}

//get max from b
float DataSet::getMaxY() {
	float largest = mySet[0].getY();
	for (int i = 0; i < 400; i++)
	{
		if (mySet[i].getY() > largest) {
			largest = mySet[i].getY();
		}
	}
	return largest;
}
//get minimum value for a
float DataSet::getMinX() {
	float smallest = mySet[0].getX();
	for (int i = 0; i < 400; i++)
	{
		if (mySet[i].getX() < smallest) {
			smallest = mySet[i].getX();
		}
	}
	return smallest;
}
//get min value for b
float DataSet::getMinY() {
	float smallest = mySet[0].getY();
	for (int i = 0; i < 400; i++)
	{
		if (mySet[i].getY() < smallest) {
			smallest = mySet[i].getY();
		}
	}
	return smallest;
}

//return a point to use
Point DataSet::getPoint(int num) {
	return mySet[num];
}

//assign a cluster to a point for tracking
void DataSet::assignCluster(int element, int cluster) {
	mySet[element].setCluster(cluster);
}

//destructor
DataSet::~DataSet() {
	
}
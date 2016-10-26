#include "DataSet.h"
#include<stdio.h>


DataSet::DataSet(Point *array, int size) {
	mySet = new Point[size];
	for (int i = 0; i < size; i++) {
		mySet[i] = array[i];
	}
}
void DataSet::PrintSet() {
	for (int i = 0; i < 400; ++i) {
		printf("Set Point %d: X = %.2f  Y = %.2f\n", i + 1, mySet[i].getX(), mySet[i].getY());
	}
}

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

Point DataSet::getPoint(int num) {
	return mySet[num];
}

void DataSet::assignCluster(int element, int cluster) {
	mySet[element].setCluster(cluster);
}

DataSet::~DataSet() {
	
}
/****************************************************************************************************************
Author: Benjamin Fields
file :point implementation file for functions
Description :contains functions to act on a point
************************************************************************************************************** */
#include "Point.h"
#include<cmath>

//constructor
Point::Point() {
	setX(0.0);
	setY(0.0);
	setCluster(0);
}

//contructor used to create from data
Point::Point(float x, float y) {
	setX(x);
	setY(y);
	setCluster(0);
	
}

float Point::getX() {
	return m_X;
}
float Point::getY() {
	return m_Y;
}

void Point::setX(float x) {
	m_X = x;
}
void Point::setY(float y) {
	m_Y = y;
}

//function used to return the euclidian distance from calling point to passed point
float Point::EuclidianDistanceTo(Point p) {
	float xterm = (this->getX() - p.getX())*(this->getX() - p.getX());
	float yterm = (this->getY() - p.getY())*(this->getY() - p.getY());

	return sqrt(xterm + yterm);
}

void Point::setCluster(int num) {
	cluster = num;
}

int Point::getCluster() {
	return cluster;
}
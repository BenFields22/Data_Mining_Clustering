/********************************************************
Author:Benjamin Fields
Date:11/22/2016
Description:Implementation of the point class.
*************************************************************/
#include "Point.h"
#include <cmath>
#include <string>

/**************************************************************
Description:constructor that builds each point with the proper 
attributes and assigns an id.
*************************************************************/
Point::Point(double x, double y,double z, int i) {
	setXCoord(x);
	setYCoord(y);
	setZCoord(z);
	setId(i);
}
/**************************************************************
Description:standard getter for id
*************************************************************/
int Point::getId() {
	return id;
}
/**************************************************************
Description:standard getter for xcoord
*************************************************************/
double Point::getXCoord() {
	return xCoord;
}
/**************************************************************
Description:standard getter for ycoord
*************************************************************/
double Point::getYCoord() {
	return yCoord;
}
/**************************************************************
Description:standard getter for zcoord
*************************************************************/
double Point::getZCoord() {
	return zCoord;
}
/**************************************************************
Description:standard setter for xcoord
*************************************************************/
void Point::setXCoord(double num) {
	xCoord = num;
}
/**************************************************************
Description:standard setter for ycoord
*************************************************************/
void Point::setYCoord(double num) {
	yCoord = num;
}
/**************************************************************
Description:standard setter for zcoord
*************************************************************/
void Point::setZCoord(double num) {
	zCoord = num;
}
/**************************************************************
Description:standard setter for the id
*************************************************************/
void Point::setId(int num) {
	id = num;
}
/**************************************************************
Description:function to calculate the euclidian distance between
two points with three dimensions. 
*************************************************************/
double Point::EuclidianDist(Point other) {
	return sqrt(pow(this->getXCoord() - other.getXCoord(), 2) + pow(this->getYCoord() - other.getYCoord(), 2) + pow(this->getZCoord() - other.getZCoord(), 2));
}
/**************************************************************
Description:function to print the point data to console for 
checking
*************************************************************/
std::string Point::printPoint() {
	return "Point "+std::to_string(id)+" [ " + std::to_string(xCoord) + " , " + std::to_string(yCoord) + " , " + std::to_string(zCoord) + " ]";
}
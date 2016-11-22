/********************************************************
Author:Benjamin Fields
Date:11/22/2016
File:Point.h
Description:Data structure to represent each data point. Each 
point in this program has three attributes related to three 
dimensions.This class also contains the function for euclidian 
distance
*************************************************************/
#ifndef POINT_H
#define POINT_H
#include <string>

class Point {
	private:
		int id;
		double xCoord;
		double yCoord;
		double zCoord;
	public:
		Point(double x, double y, double z, int i);
		int getId();
		double getXCoord();
		double getYCoord();
		double getZCoord();
		void setXCoord(double num);
		void setYCoord(double num);
		void setZCoord(double num);
		void setId(int num);
		double EuclidianDist(Point other);
		std::string printPoint();
};



#endif

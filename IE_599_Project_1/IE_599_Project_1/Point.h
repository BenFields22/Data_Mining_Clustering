/****************************************************************************************************************
Author: Benjamin Fields
file :header file for point class
Description :contains structure for class
************************************************************************************************************** */
#ifndef POINT_H
#define POINT_H

class Point {
	private:
		float m_X;
		float m_Y;
		int cluster;
	public:
		Point();
		Point(float x, float y);
		void setX(float x);
		void setY(float y);
		float getX();
		float getY();
		float EuclidianDistanceTo(Point p);
		void setCluster(int num);
		int getCluster();
};


#endif
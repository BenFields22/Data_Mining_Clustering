/********************************************************
Author:Benjamin Fields
Date:11/22/2016
Description:Data structure to contain the functionality for 
each cluster to be used in the program. This class contains
the functionality for calculating the group average between 
clusters.
*************************************************************/
#ifndef CLUSTER_H
#define CLUSTER_H
#include <vector>
#include "Point.h"
class Cluster {
	private:
		std::string id;
		std::vector<Point> ClusterPoints;
	public:
		Cluster();
		Cluster(Point p);
		void AddPoint(Point p);
		std::string getId();
		void setId(std::string s);
		void addCluster(Cluster &c);
		std::vector<Point> getCluster();
		double getAverage(Cluster c);
		void printCluster();

};


#endif

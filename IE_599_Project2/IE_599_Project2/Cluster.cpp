/********************************************************
Author:Benjamin Fields
Date:11/22/2016
File:Cluster.cpp
Description:implementation of the cluster class 
*************************************************************/
#include "Cluster.h"
#include <iostream>

/**************************************************************
Description:default constructor needed for compiliation. Default 
not needed for the execution of program.
*************************************************************/
Cluster::Cluster() {
	id = "none";
}

/**************************************************************
Description:constructor that creates the initial cluster from each
point in the data set.
*************************************************************/
Cluster::Cluster(Point p) {
	id = std::to_string(p.getId());
	ClusterPoints.push_back(p);

}

/**************************************************************
Description:wraper function to add a point to the vector contained
in the class.
*************************************************************/
void Cluster::AddPoint(Point p) {
	ClusterPoints.push_back(p);
}

/**************************************************************
Description:standard getter for the id of the cluster
*************************************************************/
std::string Cluster::getId() {
	return id;
}

/**************************************************************
Description:standard setter for the id
*************************************************************/
void Cluster::setId(std::string s) {
	id = s;
}

/**************************************************************
Description:function that allows another cluster to be added to 
another. The contents of the argument cluster are added to the calling
cluster and the id is added to represent the combined cluster.
*************************************************************/
void Cluster::addCluster(Cluster &c) {
	std::vector<Point> cluster = c.getCluster();
	for (int i = 0; i < (int)cluster.size(); i++) {
		ClusterPoints.push_back(cluster[i]);
	}
	id = id + ", " + c.getId();

}

/**************************************************************
Description:standard getter for the cluster 
*************************************************************/
std::vector<Point> Cluster::getCluster() {
	return ClusterPoints;
}

/**************************************************************
Description:function that calculates the group average distance between
two clusters. 
*************************************************************/
double Cluster::getAverage(Cluster c) {
	double averageP = 0.0;
	for (int i = 0; i < (int)ClusterPoints.size(); i++) {
		for (int j = 0; j < (int)c.getCluster().size(); j++) {
			averageP += ClusterPoints[i].EuclidianDist(c.getCluster()[j]);
		}
	}
	averageP = averageP / (double)ClusterPoints.size()*(double)c.getCluster().size();
	return averageP;
}

/**************************************************************
Description:function that prints the cluster information to the 
console for use in checking.
*************************************************************/
void Cluster::printCluster() {
	std::cout << "Cluster id: " << id << std::endl;
	std::cout << "Number of points: " << ClusterPoints.size() << std::endl;
	for (int i = 0; i < (int)ClusterPoints.size(); i++) {
		std::cout << ClusterPoints[i].printPoint() << std::endl;
	}
}

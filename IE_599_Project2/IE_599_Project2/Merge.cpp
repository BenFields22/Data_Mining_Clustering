/********************************************************
Author:Benjamin Fields
Date:11/22/2016
File:Merge.cpp
Description:implementation of the merge class 
*************************************************************/
#include "Merge.h"
#include <iostream>

/**************************************************************
Description:default constructor 
*************************************************************/
Merge::Merge() {
	id = 0;
}


/**************************************************************
Description:standard getter for id
*************************************************************/
int Merge::getId() {
	return id;
}
/**************************************************************
Description:standard getter for merge value
*************************************************************/
double Merge::getMergeValue() {
	return mergeValue;
}
/**************************************************************
Description:standard getter for cluster index
*************************************************************/
int Merge::getCluster1() {
	return cluster1;
}
/**************************************************************
Description:standard getter for cluster index
*************************************************************/
int Merge::getCluster2() {
	return cluster2;
}
/**************************************************************
Description:standard setter for id
*************************************************************/
void Merge::setId(int num) {
	id = num;
}
/**************************************************************
Description:standard setter for merge value
*************************************************************/
void Merge::setMergeValue(double num) {
	mergeValue = num;
}
/**************************************************************
Description:standard setter for setting cluster 1 index
*************************************************************/
void Merge::setCluster1(int i) {
	cluster1 = i;
}
/**************************************************************
Description:standard setter for setting cluster 2 index
*************************************************************/
void Merge::setCluster2(int i) {
	cluster2 = i;
}
/**************************************************************
Description:print function for checking in console
*************************************************************/
void Merge::printMerge() {
	std::cout << "Cluster 1 index: " << cluster1 <<" Cluster 1 id: "<<cluster1id<< std::endl;
	std::cout << "Cluster 2 index: " << cluster2 <<" Cluster 2 id: "<<cluster2id<< std::endl;
	std::cout << "Merge Value: " << mergeValue << std::endl;
	
}
/**************************************************************
Description:setter for cluster 1 strings id. this tells what points
are in each cluster.
*************************************************************/
void Merge::setcluster1id(std::string s) {
	cluster1id = s;
}
/**************************************************************
Description:setter for cluster 2 strings id. this tells what points
are in each cluster.
*************************************************************/
void Merge::setcluster2id(std::string s) {
	cluster2id = s;
}

/**************************************************************
Description:getter for cluster 1 id
*************************************************************/
std::string Merge::getCluster1ID() {
	return cluster1id;
}

/**************************************************************
Description:getter for cluster 2 id
*************************************************************/
std::string Merge::getCluster2ID() {
	return cluster2id;
}
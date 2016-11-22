/********************************************************
Author:Benjamin Fields
Date:11/22/2016
File:Clustering.cpp
Description:Implementation of the clustering class
*************************************************************/
#include "Clustering.h"
#include <iostream>

/**************************************************************
Description:getter for the clustering vector
*************************************************************/
std::vector<Cluster> Clustering::getMyClustering() {
	return myClustering;
}

/**************************************************************
Description:function that deletes the copied cluster using an
identified index
*************************************************************/
void Clustering::deleteCluster(int i){
	myClustering.erase(myClustering.begin() + i);
}

/**************************************************************
Description: wraper function to allow a new cluster to be added
to the clustering. Used in the initial creation of the clustering
*************************************************************/
void Clustering::addCluster(Cluster c) {
	myClustering.push_back(c);
}

/**************************************************************
Description:function that checks the group average distance between
each cluster in the clustering and identifies the closest clusters.
The index of the pair is recorded along with the group average. 
The merge data is passed to a merge object for final results.The 
extra cluster is deleted in the end.
*************************************************************/
Merge Clustering::calulateSmallestandMerge() {
	Merge Chosen;
	double smallest = 1000000.00;//high value to initialize minimum check
	for (int i = 0; i < (int)myClustering.size(); i++) {
		for (int j = 0; j < (int)myClustering.size(); j++) {
			if (myClustering[i].getAverage(myClustering[j]) < smallest && i != j) {
				smallest = myClustering[i].getAverage(myClustering[j]);//assign new min
				Chosen.setCluster1(i);//track values in merge object
				Chosen.setCluster2(j);
				Chosen.setcluster1id(myClustering[i].getId());
				Chosen.setcluster2id(myClustering[j].getId());
				Chosen.setMergeValue(myClustering[i].getAverage(myClustering[j]));
			}
				
		}
	}
	myClustering[Chosen.getCluster1()].addCluster(myClustering[Chosen.getCluster2()]);
	deleteCluster(Chosen.getCluster2());

	return Chosen;
}

/**************************************************************
Description:function that prints the contents of the clustering
to the console for checking.
*************************************************************/
void Clustering::printClustering() {
	for (int i = 0; i < (int)myClustering.size(); i++) {
		myClustering[i].printCluster();
	}
}


/********************************************************
Author:Benjamin Fields
Date:11/22/2016
Description:Data structure to allow for easy data management
of the clusters as the program iterates through each merge.
this class contains the functionality for identifying the closest
custers and merging them. It then deletes the copyed cluster. 
*************************************************************/
#ifndef CLUSTERING_H
#define CLUSTERING_H
#include <vector>
#include "Cluster.h"
#include "Merge.h"

class Clustering {
	private:
		std::vector<Cluster> myClustering;
	public:
		std::vector<Cluster> getMyClustering();
		void addCluster(Cluster c);
		void deleteCluster(int i);
		Merge calulateSmallestandMerge();
		void printClustering();
};
#endif

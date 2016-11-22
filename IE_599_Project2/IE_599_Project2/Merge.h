/********************************************************
Author:Benjamin Fields
Date:11/22/2016
Description:Data structure used to contain the information from
each merge. 
*************************************************************/
#ifndef MERGE_H
#define MERGE_H
#include<string>
class Merge {
	private:
		int id;
		double mergeValue;
		int cluster1;
		int cluster2;
		std::string cluster1id;
		std::string cluster2id;
	public:
		Merge();
		int getId();
		double getMergeValue();
		int getCluster1();
		int getCluster2();
		void setId(int num);
		void setMergeValue(double num);
		void setCluster1(int i);
		void setCluster2(int i);
		void printMerge();
		void setcluster1id(std::string s);
		void setcluster2id(std::string s);
		std::string getCluster1ID();
		std::string getCluster2ID();
};

#endif

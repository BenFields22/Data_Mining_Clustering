#ifndef DATASET_H
#define DATASET_H
#include "Point.h"

class DataSet {
	private:
		Point *mySet;
	public:
		DataSet(Point *array, int size);
		void PrintSet();
		~DataSet();
		float getMaxX();
		float getMaxY();
		float getMinX();
		float getMinY();
		Point getPoint(int num);
		void assignCluster(int element, int cluster);
};

#endif
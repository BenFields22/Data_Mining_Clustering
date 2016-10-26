#include <stdio.h>
#include<string>
#include "Point.h"
#include<vector>
#include "DataSet.h"
#include <stdlib.h>
#include <time.h>


void populateArrays(float *a, float *b) {
	FILE *inputFile;
	inputFile = fopen("InputData_A.txt", "r");
	if (inputFile == NULL) {
		throw "fileNotFound";
	}
	else {
		printf("FILE A FOUND\n");
		for (int i = 0; i < 400; i++) {
			fscanf(inputFile, "%f", &a[i]);
		}
		fclose(inputFile);
	}
	inputFile = fopen("InputData_B.txt", "r");
	if (inputFile == NULL) {
		throw "fileNotFound";
	}
	else {
		printf("FILE A FOUND\n");
		for (int i = 0; i < 400; i++) {
			fscanf(inputFile, "%f", &b[i]);
		}
		fclose(inputFile);
	}
}

 Point *createPoints(int size,float *a,float *b) {
	Point *myarray = new Point[size];
	for (int i = 0; i < size; i++)
	{
		myarray[i].setX(a[i]);
		myarray[i].setY(b[i]);
	}
	return myarray;
}

Point* createCentroids(int num, DataSet &set) {
	Point *centroids = new Point[num];
	int index = 0;
	while (index < num) {
		
		float x, y;
		x = set.getMinX() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (set.getMaxX() - set.getMinX())));
		centroids[index].setX(x);

		y = set.getMinY() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (set.getMaxY() - set.getMinY()+.01)));
		centroids[index].setY(y);

		if (index == 0) {
			index++;
			continue;
		}
		bool accept = true;
		for (int i = 0; i < index; i++) {
			
			if (abs(centroids[i].getX() - centroids[index].getX()) > .0001&&abs(centroids[i].getY() - centroids[index].getY()) > .0001) {
				
				continue;
			}
			else {
				accept = false;
				break;
			}
		}
		if (accept == true) {
			index++;
		}
	}
	return centroids;
}

void kmeans(DataSet set, int numKs) {
	std::vector< std::vector<Point> > myClusters(numKs);

	Point* myCentroids = createCentroids(numKs, set);
	for (int i = 0; i < numKs; i++) {
		printf("centroid %d: %.2f, %.2f\n", i + 1, myCentroids[i].getX(), myCentroids[i].getY());
	}
	
	for (int j = 0; j < 400; j++)
	{
		int smallest = 0;
		for (int i = 0; i < numKs; i++)
		{
			if (set.getPoint(j).EuclidianDistanceTo(myCentroids[i]) < set.getPoint(j).EuclidianDistanceTo(myCentroids[smallest])) {
				smallest = i;
			}
		}
		printf("Point %d was closest to centoid %d\n", j+1,smallest);
		set.assignCluster(j,smallest);
		printf("Point %d assigned to cluster %d\n", j+1,set.getPoint(j).getCluster());
		myClusters[smallest].push_back(set.getPoint(j));
	}

	for (int i = 0; i < numKs; i++) {

		printf("Cluster %d has %d elements\n",i+1, myClusters[i].size());
	}

	Point *newCentroids = new Point[numKs];

	for (int i = 0; i < numKs; i++) {
		float xSum = 0.0f;
		float ySum = 0.0f;
		for (int j = 0; j < (int)myClusters[i].size(); j++) {
			xSum += myClusters[i][j].getX();
			ySum += myClusters[i][j].getY();
		}
		int sizeofCluster = myClusters[i].size();
		if (sizeofCluster == 0)sizeofCluster = 1;
		float averageX = xSum / (float)sizeofCluster;
		float averagey = ySum / (float)sizeofCluster;
		newCentroids[i].setX(averageX);
		newCentroids[i].setY(averagey);
	}

	for (int i = 0; i < numKs; i++) {
		printf("The new centroid for cluster %d is %.2f,%.2f\n", i + 1, newCentroids[i].getX(), newCentroids[i].getY());
	}

	//TODO sum of squared error based on each point distance to average centroid
	//TODO create functions to allow for looping of each iteration

}

int main(int argc, char **argv) {
	unsigned int seed = (unsigned int)time(0);
	srand(seed);
	float *a,*b;
	a = (float*)malloc(400 * sizeof(float));
	b = (float*)malloc(400 * sizeof(float));
	try {
		populateArrays(a, b);
	}
	catch (std::string) {
		printf("DATA FILE COULD NOT BE FOUND!\n");
		exit(EXIT_FAILURE);
	}
	
	Point *myPoints= createPoints(400, a, b);
	DataSet mySet(myPoints, 400);
	mySet.PrintSet();
	
	printf("The largest in A is %.2f and the largest in B is %.2f\n", mySet.getMaxX(), mySet.getMaxY());
	printf("The smallest in A is %.2f and the smallest in B is %.2f\n", mySet.getMinX(), mySet.getMinY());

	kmeans(mySet, 3);

	//printf("back in main the assigned cluster for element 400 is %d\n", mySet.getPoint(399).getCluster());

	free(a);
	free(b);

	system("PAUSE");
	return 0;
}
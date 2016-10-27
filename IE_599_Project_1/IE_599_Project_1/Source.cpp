#include <stdio.h>
#include<string>
#include "Point.h"
#include<vector>
#include "DataSet.h"
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include<fstream>
#include<iomanip>


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
		printf("FILE B FOUND\n");
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

 Point* createTwoCentroidsB(std::vector<Point> initCluster) {
	 float largestX = initCluster[0].getX();
	 for (int i = 0; i < (int)initCluster.size(); i++)
	 {
		 if (initCluster[i].getX() > largestX) {
			 largestX = initCluster[i].getX();
		 }
	 }

	 float largestY = initCluster[0].getY();
	 for (int i = 0; i < (int)initCluster.size(); i++)
	 {
		 if (initCluster[i].getY() > largestY) {
			 largestY = initCluster[i].getY();
		 }
	 }

	 float minX = initCluster[0].getX();
	 for (int i = 0; i < (int)initCluster.size(); i++)
	 {
		 if (initCluster[i].getX() < minX) {
			 minX = initCluster[i].getX();
		 }
	 }
	 float minY = initCluster[0].getY();
	 for (int i = 0; i < (int)initCluster.size(); i++)
	 {
		 if (initCluster[i].getY() < minX) {
			 minX = initCluster[i].getY();
		 }
	 }

	 
	 Point *centroids = new Point[2];
	 int index = 0;
	 while (index < 2) {

		 float x, y;
		 x = minX + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (largestX - minX)));
		 centroids[index].setX(x);

		 y = minY + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (largestY - minY)));
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

void assignPointsToCentroids(DataSet set,std::vector<std::vector<Point> > &myClusters, Point* myCentroids,int numKs) {
	for (int j = 0; j < 400; j++)
	{
		int smallest = 0;
		for (int i = 0; i < numKs; i++)
		{
			if (set.getPoint(j).EuclidianDistanceTo(myCentroids[i]) < set.getPoint(j).EuclidianDistanceTo(myCentroids[smallest])) {
				smallest = i;
			}
		}
		
		set.assignCluster(j, smallest);
		
		myClusters[smallest].push_back(set.getPoint(j));
	}
}
void assignPointsToCentroidsB(std::vector<Point> &initCluster, std::vector<std::vector<Point> > &myClusters, Point* myCentroids, int numKs) {
	for (int j = 0; j < (int)initCluster.size(); j++)
	{
		int smallest = 0;
		for (int i = 0; i < numKs; i++)
		{
			if (initCluster[j].EuclidianDistanceTo(myCentroids[i]) < initCluster[j].EuclidianDistanceTo(myCentroids[smallest])) {
				smallest = i;
			}
		}
		
		initCluster[j].setCluster(smallest);
		
		myClusters[smallest].push_back(initCluster[j]);
	}
}

Point* CalculateNewAverages(std::vector<std::vector<Point> > &myClusters,int numKs) {
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

	return newCentroids;
}

float *calcSSEofClusters(std::vector<std::vector<Point> > &myClusters,Point *newCentroids, int numKs) {
	float *SSEofClusters = new float[numKs];
	for (int i = 0; i < numKs; i++) {
		float sum = 0.0;
		for (int j = 0; j < (int)myClusters[i].size(); j++) {
			sum += (myClusters[i][j].EuclidianDistanceTo(newCentroids[i]))*(myClusters[i][j].EuclidianDistanceTo(newCentroids[i]));
		}
		SSEofClusters[i] = sum;
	}

	return SSEofClusters;
}

float calculateTotalSSE(float *SSEofClusters, int numKs) {
	float total = 0.0;
	for (int i = 0; i < numKs; i++) {
		total += SSEofClusters[i];
	}

	return total;
}

void writeToFile(std::vector< std::vector<Point> > &myClusters, int numKs,int iteration,float * SSE,float totSSE) {
	std::ofstream myFile;
	myFile.open("Results.csv");
	myFile << "Clustering Results after "<<iteration<<" iterations:\n\n";
	for (int i = 0; i < myClusters.size(); i++) {
		myFile << "SSE of cluster ," << i + 1 << " : " << SSE[i] << "\n";
	}
	myFile << "Total SSE: ," << totSSE << "\n";
	for (int i = 0; i < numKs; i++) {
		myFile << "Cluster: " << i + 1 << "\n";
		myFile << "Data:\n";
		for (int j = 0; j < (int)myClusters[i].size(); j++) {
			myFile << myClusters[i][j].getX() << ",";
		}
		myFile << "\n";
		for (int j = 0; j < (int)myClusters[i].size(); j++) {
			myFile << myClusters[i][j].getY() << ",";
		}
		myFile << "\n";
	}
	myFile.close();

}

std::vector< std::vector<Point> > loopKmeans(DataSet set, int numKs, Point *initialCentroids){
	int iteration = 1;
	bool stop = false;
	std::vector< std::vector<Point> > myClusters(numKs);
	
	
	while (stop == false) {
		iteration++;
		assignPointsToCentroids(set, myClusters, initialCentroids, numKs);
		Point *newCentroids = CalculateNewAverages(myClusters, numKs);
		float *SSEofClusters = calcSSEofClusters(myClusters, newCentroids, numKs);
		float totSSE = calculateTotalSSE(SSEofClusters, numKs);
		printf("\niteration %d\n", iteration);
		for (int i = 0; i < numKs; i++) {
			printf("The SSE of cluster %d is %.2f\n", i + 1, SSEofClusters[i]);
		}
		printf("The total SSE is %.2f\n", totSSE);
		stop = true;
		for (int i = 0; i < numKs; i++) {
			if (newCentroids[i].EuclidianDistanceTo(initialCentroids[i]) < .0001) {
				continue;
			}
			else {
				stop = false;
			}
		}
		if (stop == false) {
			for (int i = 0; i < numKs; i++) {
				initialCentroids[i] = newCentroids[i];
				myClusters[i].clear();
			}
		}
	}
	Point *newCentroids = CalculateNewAverages(myClusters, numKs);
	float *SSEofClusters = calcSSEofClusters(myClusters, newCentroids, numKs);
	float totSSE = calculateTotalSSE(SSEofClusters, numKs);
	printf("Kmeans has converged afer %d iterations\n", iteration);
	//writeToFile(myClusters, numKs,iteration,SSEofClusters,totSSE);
	return myClusters;
}
std::vector< std::vector<Point> > loopKmeansB(std::vector<Point> init, int numKs, Point *initialCentroids) {
	int iteration = 1;
	bool stop = false;
	std::vector< std::vector<Point> > myClusters(numKs);
	
	while (stop == false) {
		iteration++;
		assignPointsToCentroidsB(init, myClusters, initialCentroids, numKs);
		Point *newCentroids = CalculateNewAverages(myClusters, numKs);
		float *SSEofClusters = calcSSEofClusters(myClusters, newCentroids, numKs);
		float totSSE = calculateTotalSSE(SSEofClusters, numKs);
		/*printf("\niteration %d\n", iteration);
		for (int i = 0; i < numKs; i++) {
			printf("The SSE of cluster %d is %.2f\n", i + 1, SSEofClusters[i]);
		}
		printf("The total SSE is %.2f\n", totSSE);*/
		stop = true;
		for (int i = 0; i < numKs; i++) {
			if (newCentroids[i].EuclidianDistanceTo(initialCentroids[i]) < .0001) {
				continue;
			}
			else {
				stop = false;
			}
		}
		if (stop == false) {
			for (int i = 0; i < numKs; i++) {
				initialCentroids[i] = newCentroids[i];
				myClusters[i].clear();
			}
		}
	}
	printf("Kmeans has converged afer %d iterations\n", iteration);
	Point *newCentroids = CalculateNewAverages(myClusters, numKs);
	float *SSEofClusters = calcSSEofClusters(myClusters, newCentroids, numKs);
	float totSSE = calculateTotalSSE(SSEofClusters, numKs);
	//writeToFile(myClusters, numKs, iteration,SSEofClusters,totSSE);
	return myClusters;
}

void kmeans(DataSet set, int numKs, std::vector< std::vector<Point> > &InitClusters,int posRemove) {
	printf("\nIteration 1\n");
	std::vector< std::vector<Point> > myClusters(numKs);
	Point* myCentroids = createCentroids(numKs, set);
	assignPointsToCentroids(set, myClusters, myCentroids, numKs);
	Point *newCentroids = CalculateNewAverages(myClusters, numKs);
	float *SSEofClusters = calcSSEofClusters(myClusters,newCentroids,numKs);
	float totSSE = calculateTotalSSE(SSEofClusters,numKs);
	for (int i = 0; i < numKs; i++) {
		printf("The SSE of cluster %d is %.2f\n", i + 1, SSEofClusters[i]);
	}
	printf("The total SSE is %.2f\n", totSSE);
	
	myClusters = loopKmeans(set, numKs, newCentroids);
	
}
void kmeansB(int numKs, std::vector<Point> &InitCluster, int posRemove, std::vector< std::vector<Point> > &myClusters) {
	printf("\nIteration 1\n");
	std::vector< std::vector<Point> > newClusters(2);
	Point* myCentroids = createTwoCentroidsB(InitCluster);
	assignPointsToCentroidsB(InitCluster, newClusters, myCentroids, 2);
	Point *newCentroids = CalculateNewAverages(newClusters, 2);
	float *SSEofClusters = calcSSEofClusters(newClusters, newCentroids, 2);
	float totSSE = calculateTotalSSE(SSEofClusters, 2);
	for (int i = 0; i < numKs; i++) {
		printf("The SSE of cluster %d is %.2f\n", i + 1, SSEofClusters[i]);
	}
	printf("The total SSE is %.2f\n", totSSE);
	newClusters = loopKmeansB(InitCluster, numKs, newCentroids);
	myClusters.erase(myClusters.begin() + posRemove);
	for (int i = 0; i < 2; i++) {

		myClusters.push_back(newClusters[i]);
	}
	
}

std::vector< std::vector<Point> > bisectingKmeans(DataSet &set,int numKs) {
	std::vector< std::vector<Point> > myClusters(1);
	
	
	for (int i = 0; i < 400; i++) {
		myClusters[0].push_back(set.getPoint(i));
	}
	int posRemove = 0;
	printf("Cluster size is: %d\n", myClusters.size());
	bool stop = false;
	//kmeans(set, 2, myClusters,posRemove);
	//printf("The number of clusters after is %d\n", myClusters.size());
	int iteration = 0;
	while ((int)myClusters.size() < numKs) {
		iteration++;
		kmeansB(2, myClusters[posRemove],posRemove,myClusters);
		//printf("The number of clusters after is %d\n", myClusters.size());
		Point *averages = CalculateNewAverages(myClusters, myClusters.size());
		float *SSEofClusters = calcSSEofClusters(myClusters, averages, myClusters.size());
		
		int biggest = 0;
		for (int i = 0; i < (int)myClusters.size(); i++) {
			if (SSEofClusters[i] > SSEofClusters[biggest]) {
				biggest = i;
			}
		}
		posRemove = biggest;
		
	}
	Point *averages = CalculateNewAverages(myClusters, myClusters.size());
	float *SSEofClusters = calcSSEofClusters(myClusters, averages, myClusters.size());
	float totSSE = calculateTotalSSE(SSEofClusters, myClusters.size());
	printf("Bisecting K-means complete with %d clusters after %d iterations\n\n", myClusters.size(),iteration);
	for (int i = 0; i < (int)myClusters.size(); i++) {
		printf("The SSE of cluster %d is %f\n", i + 1, SSEofClusters[i]);
	}
	printf("The total SSE is : %f\n", totSSE);
	writeToFile(myClusters, numKs,iteration, SSEofClusters,totSSE);
	return myClusters;
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

	//kmeans(mySet, 3);
	std::vector< std::vector<Point> >myClusters = bisectingKmeans(mySet, 3);

	for (int i = 0; i < (int)myClusters.size(); i++) {
		printf("Cluster %d has %d elements\n", i + 1, myClusters[i].size());
	}

	free(a);
	free(b);

	system("PAUSE");
	return 0;
}
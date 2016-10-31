#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

void populateVector(std::vector<float> &myData) {
	std::ifstream inputFile;
	inputFile.open("Output.txt");
	float value;
	if (inputFile) {
		while (inputFile >> value) {
			myData.push_back(value);
		}
		inputFile.close();
	}
	else {
		std::cout << "Could not open File!" << std::endl;
	}
}

void printVector(std::vector<float> &myData) {
	for (int i = 0; i < (int)myData.size(); i++) {
		std::cout << "Data point " << i + 1 << " : " << myData[i] << std::endl;
	}
}

std::vector<float> createVector1(std::vector<float> &myData, int sizeCheck) {
	std::vector<float> vector1;
	for (int i = 0; i < sizeCheck; i++) {
		vector1.push_back(myData[i]);
	}
	return vector1;
}

std::vector<float> createVector2(std::vector<float> &myData, int sizeCheck) {
	std::vector<float> vector2;
	for (int i = sizeCheck; i < sizeCheck+sizeCheck; i++) {
		vector2.push_back(myData[i]);
	}
	return vector2;
}

float dotProduct(std::vector<float> &vec1, std::vector<float> &vec2) {
	float sum = 0.0;
	for (int i = 0; i < (int)vec1.size(); i++) {
		sum += vec1[i] * vec2[i];
	}

	return sum;
}

float magnitude(std::vector<float> &myVector) {
	float mag = 0.0;
	for (int i = 0; i < (int)myVector.size(); i++) {
		mag += myVector[i] * myVector[i];
	}
	return sqrt(mag);
}

float cosineSim(std::vector<float> &vec1, std::vector<float> &vec2) {
	float dot = dotProduct(vec1, vec2);
	float xCard = magnitude(vec1);
	float yCard = magnitude(vec2);
	return dot / (xCard*yCard);
}

std::vector<float> createVector2Check(std::vector<float> &myData, int start,int sizeCheck) {
	std::vector<float> vector2;
	for (int i = start; i < start + sizeCheck; i++) {
		vector2.push_back(myData[i]);
	}
	return vector2;
}

bool checkPattern(std::vector<float> &myData, int CheckSize, int limit, float originalCos) {
	

	int checkNum = 1;
	float sum = 0.0;
	while (checkNum < limit) {
		std::vector<float> vector1 = createVector1(myData, CheckSize);
		std::vector<float> vector2 = createVector2Check(myData, CheckSize*checkNum,CheckSize);
		//std::cout << "Vector 1: \n";
		//printVector(vector1);
		//std::cout << "Vector 2: \n";
		//printVector(vector2);
		sum += cosineSim(vector1, vector2);
		vector2.clear();
		checkNum++;
	}
	float average = sum / float(limit);
	bool pass;
	if (abs(average - originalCos) < .1) {
		pass = true;
	}
	else {
		pass = false;
	}

	return pass;
}
int findProcess(std::vector<float> &myData, int limit) {
	
	int numProcesses = -1;
	int sizeCheck = 2;
	while (sizeCheck < limit) {
		std::vector<float> vector1 = createVector1(myData, sizeCheck);
		std::vector<float> vector2 = createVector2(myData, sizeCheck);
		float cosSim = cosineSim(vector1, vector2);
		bool found = false;
		if ((1 - cosSim) < .01) {
			found = checkPattern(myData, sizeCheck,20,cosSim);
		}
		if (found == true) {
			std::cout << "Pattern found with " << sizeCheck << " Processes \n\n";
			numProcesses = sizeCheck;
			break;
		}
		//float()
		/*
		std::cout << "\nTest size: " << sizeCheck << std::endl;
		std::cout << "Vector 1: \n";
		printVector(vector1);
		std::cout << "Vector 2: \n";
		printVector(vector2);
		std::cout << "Cosine Similarity: " << cosSim << std::endl;*/
		sizeCheck++;
	}

	return numProcesses;
}

bool firstCheck(std::vector<float> &myData) {
	bool oneCheck = true;
	for (int i = 1; i < (int)myData.size(); i++) {
		if (abs(myData[0]- myData[i])>.1) {
			oneCheck = false;
			break;
		}
	}
	return oneCheck;
}

void findAverageProcessTimes(std::vector<float> &myData, float *averages, int size) {
	for (int i = 0; i < size; i++) {
		float sum = 0.0;
		int count = 0;
		for (int j = i; j < (int)myData.size();) {
			sum += myData[j];
			count++;
			j = j + size;
		}
		float average = sum / (float)count;
		averages[i] = average;
	}
}

void printAverages(float *averages, int size) {
	std::cout << "Average times for each process: \n";
	for (int i = 0; i < size; i++) {
		std::cout << "Process " << i + 1 << " : " << averages[i] << " minutes "<<std::endl;
	}
}

void findStdDev(std::vector<float> &myData, float *averages, int numProcesses,float *stddev) {
	for (int i = 0; i < numProcesses; i++) {
		float sum = 0.0;
		int count = 0;
		for (int j = i; j < (int)myData.size();) {
			sum += (myData[j]-averages[i])* (myData[j] - averages[i]);
			count++;
			j = j + numProcesses;
		}
		float dividebyn = sum / (float)count;
		stddev[i] = sqrt(dividebyn);
	}
}
void printStdDev(float *stddev, int size) {
	std::cout << "\nStandard Deviations for each process: \n";
	for (int i = 0; i < size; i++) {
		std::cout << "Process " << i + 1 << " : " << stddev[i] << std::endl;
	}
}

int main(int argc, char **argv) {
	std::vector<float> myData;
	int numProcesses;
	populateVector(myData);
	//printVector(myData);
	bool check = firstCheck(myData);
	if (check != true) {
		numProcesses = findProcess(myData,10);
	}

	if (numProcesses == -1) {
		std::cout << "NO PROCESS PATTERN FOUND\n";
	}
	else {
		float *averages = new float[numProcesses];
		findAverageProcessTimes(myData, averages, numProcesses);
		printAverages(averages, numProcesses);
		float *stddev = new float[numProcesses];
		findStdDev(myData, averages, numProcesses,stddev);
		printStdDev(stddev, numProcesses);
	}

	system("PAUSE");
	return 0;
}
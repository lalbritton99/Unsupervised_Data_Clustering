#ifndef FILER
#define FILER

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

struct point {
	double x;
	double y;
	int ID;
	int clustID;
	double distToCentroid;
};

map<int, point> reader(int *kMin, int *kMax, vector<vector<int>> *centroidNum);


#endif

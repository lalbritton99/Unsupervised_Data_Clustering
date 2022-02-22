/*
 * KMeans.h
 *
 *  Created on: Oct 23, 2019
 *      Author: logan
 */

#ifndef KMEANS_H_
#define KMEANS_H_

#include <cmath>
#include <vector>
#include <map>
//#include <fstream> // QGIS testing //FIXME
#include "filer.h"
#include "DunnIndex.h"
using namespace std;


struct DunnIndex KMeans(vector<vector<int>> CIDs, map<int, point> Points, int KMax, int KMin);


#endif /* KMEANS_H_ */

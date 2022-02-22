/*
 * DunnIndex.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Austin
 */

#ifndef DUNNINDEX_H_
#define DUNNINDEX_H_

#include <iostream>
#include <map>
#include <float.h>
#include "filer.h"
#include "KMeans.h"
#include "EuclideanDistance.h"
using namespace std;

struct DunnIndex {
	double kMeansDunnIndex = 0;			// highest dunn index value for kmeans clustering
	double CLHDunnIndex = 0;			// highest dunn index value for centroid-linkage hierarchical clustering
	int kValue = 0;						// the value of K that gave the highest value
	int CLHLevel = 0;					// the level for CLH that gave the highest dunn index

};

double calculateDunnIndex(double inter, double intra);
		// inter: shortest distance between two points in different clusters
		// intra: largest distance between two points in a single cluster

		// takes in two floating point numbers, the inter-cluster distance and intra-cluster distance
		// for any two points, and divides them to get the ration between them. Function
		// returns a double for the Dunn Index for a given cluster.

		// Want clusters with a high Dunn Index.
		// Want a high inter distance and a low intra distance

double findInterDistance(map<int, point> Points, map<int,point>::iterator itr);
		// will take in the map of points, and the current loop iterator and find the
		// shortest distance between two points in different clusters

double findIntraDistance(map<int, point> Points, map<int,point>::iterator itr);
		// will take in the map of points, and the current loop iterator and find the
		// largest distance between two points in the same clusters

#endif /* DUNNINDEX_H_ */

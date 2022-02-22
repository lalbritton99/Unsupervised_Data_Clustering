/*
 * CPMain.cpp
 *
 *  Created on: Oct 15, 2019
 *      Author: Group 7
 */
#include "filer.h"
#include "DunnIndex.h"
#include "KMeans.h"
#include <iostream>
using namespace std;

int main() {
//---------------------------------------------------------------------- Reading In ----------------------------------------------------------


	/*
	 * map index is coordinate ID, struct point has
	 * double 'x' for x values, double 'y' for y values, and int
	 * clustID for the cluster the point resides in
	 */
	
	map<int, point> kMeans; 					//points for k-means clustering
	map<int, point> CLH; 						//points for centroid-linkage hierarchical clustering
	vector<vector<int>> centroidNum; 			//centroids to be used when starting
	int kMax, kMin; 							//Maximum and minimum clusters to be made
	DunnIndex kMeansDunnIndex;					// instance of DunnIndex struct for KMeans variables
	DunnIndex CLHDunnIndex;						// instance of DunnIndex struct for CHL variables
	
	kMeans = reader(&kMin, &kMax, &centroidNum);
	CLH = kMeans;
	cout << "The total number of k values to be tested is " << centroidNum.size() << endl;
	cout << "The total number of points in this file is " << kMeans.size() << endl << endl;

//-------------------------------------------------------------------- End Reading In --------------------------------------------------------


//-------------------------------------------------------------------- Begin K-Means ---------------------------------------------------------
	kMeansDunnIndex = KMeans(centroidNum, kMeans, kMax, kMin);
//--------------------------------------------------------------------- End K-Means ----------------------------------------------------------


//---------------------------------------------------------------- Begin Dunn Index Ouput ----------------------------------------------------
	cout << "For k-means, a k value of " << kMeansDunnIndex.kValue << " had the highest Dunn index of " << kMeansDunnIndex.kMeansDunnIndex << endl;
	cout << "For centroid-linkage hierarchical clustering level " << CLHDunnIndex.CLHLevel << " had the highest Dunn index of " << CLHDunnIndex.CLHDunnIndex << endl;
//----------------------------------------------------------------- End Dunn Index Ouput -----------------------------------------------------
	return 0;
}






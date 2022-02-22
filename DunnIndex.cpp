/*
 * DunnIndex.cpp
 *
 *  Created on: Oct 21, 2019
 *      Author: Austin
 */
#include "DunnIndex.h"

double calculateDunnIndex(double inter, double intra) {
	if(intra == 0)
	{
		return 0;
	}
	else
	{
		return inter / intra;
	}
}

double findInterDistance(map<int, point> Points, map<int,point>::iterator itr){
	double interDistance = DBL_MAX;				// holds the inter-cluster distance initialized to max val for a double
	double tempInter = 0;						// temp var for interDistance

	for(map<int,point>::iterator itr2 = Points.begin(); itr2 != Points.end(); itr2++)	// loop through all points
	{
		if((itr->first != itr2->first) && (itr2->second.clustID != itr->second.clustID))	// if not the same point AND not in same cluster
		{
			tempInter = calculateEuclidieanDistance(itr->second, itr2->second);
			if(tempInter < interDistance)		// check if the temporary distance is greater than the current interDistance OR if the first loop
			{
				interDistance = tempInter;		// if so, set the interDistance to the temp
			}
		}
	}

	return interDistance;
}

double findIntraDistance(map<int, point> Points, map<int,point>::iterator itr){
	double intraDistance = 0;				// holds the intra-cluster distance
	double tempIntra = 0;					// temp var for intraDistance

	for(map<int,point>::iterator itr2 = Points.begin(); itr2 != Points.end(); itr2++)	// loop through all points
	{
		if((itr->first != itr2->first) && (itr2->second.clustID == itr->second.clustID))	// if not the same point AND in same cluster
		{
			tempIntra = calculateEuclidieanDistance(itr->second, itr2->second);
			if(tempIntra > intraDistance) 		// check if the temporary distance is greater than the current intraDistance
			{
				intraDistance = tempIntra;		// if so, set the intraDistance to the temp
			}
		}
	}

	return intraDistance;
}



/*
 * EuclideanDistance.cpp
 *
 *  Created on: Oct 21, 2019
 *      Author: Austin
 */

#include "EuclideanDistance.h"

double calculateEuclidieanDistance(point P1, point P2){

	double eucDist;

	eucDist = sqrt((pow(((P1.x)-(P2.x)),2) + (pow(((P1.y)-(P2.y)),2))));

	return eucDist;
}



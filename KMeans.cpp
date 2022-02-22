/*
 * KMeans.cpp
 *
 *  Created on: Oct 23, 2019
 *      Author: logan
 */
#include "KMeans.h"
#include "EuclideanDistance.h"
#include <float.h>

DunnIndex KMeans(vector<vector<int>> CIDs, map<int, point> Points, int KMax, int KMin){

		vector<vector<point>> centroids;															// holds beginning centroid points
		double interDistance = 0;																	// holds the inter-cluster distance (see DunnIndex.h)
		double intraDistance = 0;																	// holds the intra-cluster distance (see DunnIndex.h)
		double tempIntra = 0;																		// temp var for intraDistance
		double tempInter = 0;																		// temp var for interDistance
		double dunnIndex = 0;																		// holds the dunnIndex for each cluster
		DunnIndex finalDunnIndex; 																	// holds the highest dunn index for KMeans

		//ofstream ofile; //FIXME // For use with QGIS
		//ofstream o2file; //FIXME
	//===================================================== Begin K-Means ==================================================================

	cout << "For K-Means Clustering: " << endl;

	for(int K = KMin; K <= KMax; K++){ 															// For each K value (# of centroids)

		//===================================== BEGIN Convert Centroid IDs to Points ===================================================
		//resets centroids to initial positions for every K

		for(int k = KMin; k <= KMax; k++){																// loop through all K values
			vector<point> tempPoints;																	// holds centroids for each K

				for(int N = 0; N < k; N++){																// loop through centroid IDs

					for(map<int,point>::iterator itr = Points.begin(); itr != Points.end(); itr++){		// loop through points

						if((itr->second).ID == CIDs[k-KMin][N]){										// if point ID == centroid ID
							point tempP = (itr->second);
							tempP.ID = N+1;																// assign index to ID
							tempPoints.push_back(tempP);												// store point
						}
					}
				}
			centroids.push_back(tempPoints);															// store vector of points
		}

		//===================================== END Convert Centroid IDs to Points ===================================================

		// For each K, initializes points to the first cluster for comparisons
		for(map<int,point>::iterator itr = Points.begin(); itr != Points.end(); itr++){						// loop through points

			itr->second.distToCentroid = calculateEuclidieanDistance(itr->second, centroids[K-KMin][0]); 	// init distToCentroid to first centroid
			itr->second.clustID = centroids[K-KMin][0].ID; 													// init to first cluster
		}

		//================================ START Iterate until converged ==========================================

		bool converge = false;									// truth val for if clusters have converged

		while(!converge){ 										// While not converged (1 or more points move clusters)

			converge = true;									// set converge to true


			//---------------------- Point Cluster Assignment ---------------------

			for(map<int,point>::iterator itr = Points.begin(); itr != Points.end(); itr++){ 		// For each point, assign to nearest centroid

				itr->second.distToCentroid = calculateEuclidieanDistance(itr->second, centroids[K-KMin][(itr->second.clustID)-1]); 	// init distToCentroid to previously closest centroid

				for(int i=0; i<K; i++){ 															// loop through each centroid of K

					double tempDist = calculateEuclidieanDistance(itr->second, centroids[K-KMin][i]); // calculate dist from each centroid


					if(tempDist < itr->second.distToCentroid){ 										// if distance is less to centroid than previously closest

						(itr->second).distToCentroid = tempDist;									// set new minimum distance

						if((itr->second.clustID != centroids[K-KMin][i].ID)){						// If centroid is from a diferent cluster than previously closest
							(itr->second).clustID = (centroids[K-KMin][i]).ID;							// set point to new cluster
							converge = false;															// not converged
						}
					}
					else if(tempDist == itr->second.distToCentroid){								// if distances between centroids are equal

						if(centroids[K-KMin][i].ID < (itr->second).clustID){						// if the curently checked centroid ID is lesser
							(itr->second).clustID = centroids[K-KMin][i].ID;						// assign the point to the cluster with the lesser ID
							converge = false; 														// not converged
						}
					}
				}
			}





			//------------------------- Move Centroids -------------------------

			for(int C = 0; C < K; C++){ 															// For every cluster, reassign centroid to center

				double sumX = 0; 		//init x value sum to 0
				double sumY = 0;		//init y value sum to 0
				int pointsInClust = 0;	//init points in the cluster to 0

				for(map<int,point>::iterator itr = Points.begin(); itr != Points.end(); itr++){ 	// loop through all points
					if((itr->second).clustID == centroids[K-KMin][C].ID){ 							// if point is in cluster
						sumX += (itr->second).x;													// add coordinates to sums and increment point counter
						sumY += (itr->second).y;
						pointsInClust++;
					}
				}

				(centroids[K-KMin][C]).x = (sumX / pointsInClust);									// reassign x of cluster centroid to average of x values in cluster
				(centroids[K-KMin][C]).y = (sumY / pointsInClust);									// reassign y of cluster centroid to average of y values in cluster
			}
		}

		//================================ END Iterate until converged ==========================================



		//============================================ START K Outputs ============================================

		//----------------------- START TESTING WITH QGIS ----------------------------

		/*switch(K){  //FIXME
		case 2:
			cout << "Opened K2Test" << endl;
			 ofile.open("K2Test.txt"); //FIXME
			 o2file.open("K2TestC.txt"); //FIXME

			break;

		case 3:
			ofile.close();
			o2file.close();
			 ofile.open("K3Test.txt"); //FIXME
			 o2file.open("K3TestC.txt"); //FIXME
			break;

		case 4:
			ofile.close();
			o2file.close();
			 ofile.open("K4Test.txt"); //FIXME
			 o2file.open("K4TestC.txt"); //FIXME
			break;

		case 5:
			ofile.close();
			o2file.close();
			 ofile.open("K5Test.txt"); //FIXME			 o2file.open("K5TestC.txt"); //FIXME
			break;

		default:
			cout << "Opened Junk" << endl;
			 //ofile.open("junk.txt"); //FIXME
			// o2file.open("junkC.txt"); //FIXME
		}


		for(map<int,point>::iterator itr = Points.begin(); itr != Points.end(); itr++){	 	// output of points with cluster ID		//FIXME
			ofile << itr->second.x << "\t" << itr->second.y << "\t" << itr->second.clustID << "\t" << K << endl; //FIXME
		}

		for(int i =0; i < K; i++){ 		// output of centroid locations //FIXME
			o2file << centroids[K-KMin][i].x << "\t" << centroids[K-KMin][i].y << endl;
		}
		o2file << endl;
		 */
		//----------------------- END TESTING WITH QGIS ----------------------------


		// Output Cluster IDs, # of points in clusters, and Point ID closest to centroid
		cout << "For a K-Value of " << K << ", here is the information regarding its clusters:" << endl;

		for(int k = 0; k < K; k++){ 														// loop through clusters of current K-Value

			int clusterPointCount = 0; 														// num of points in cluster
			point closestPoint;																// closest point to centroid
			interDistance = DBL_MAX;														// holds the inter-cluster distance initialized to max val of a double
			if(k == 0)																		// for first loop only
			{
				intraDistance = 0;															// holds the intra-cluster distance initialized to zero
			}

			for(map<int,point>::iterator itr = Points.begin(); itr != Points.end(); itr++){ // loop through all points

				if((itr->second).clustID == (centroids[K-KMin][k]).ID){ 						// if point is in cluster

					clusterPointCount++; 														// increment point counter

					if(clusterPointCount == 1){ 												// if first point in cluster
						closestPoint = (itr->second); 												// assign first point as closest
					}
					else if((itr->second).distToCentroid < closestPoint.distToCentroid){ 		// if distance is less than any before
						closestPoint = (itr->second); 												// assign point as closest
					}

					//------------------- Calculating Intra-Cluster Distance -------------------
					tempIntra = findIntraDistance(Points, itr);
					if(tempIntra > intraDistance) 											// check if the temporary distance is greater than the current intraDistance
					{
						intraDistance = tempIntra;
					}
				}
				else																		// if point is NOT in the cluster
				{
					//------------------- Calculating Inter-Cluster Distance -------------------
					tempInter = findInterDistance(Points, itr);
					if(tempInter < interDistance)		// check if the temporary distance is less than the current interDistance OR if the first loop
					{
						interDistance = tempInter;		// if so, set the interDistance to the temp
					}
				}
			}

			cout << "Cluster " << k+1 << " contains " << clusterPointCount << " points and the point " << closestPoint.ID << " is closest to its centroid." << endl;
		}

		//============================================ END K Outputs ============================================

		//------------------------------------------- Dunn Index Outputs ------------------------------------------------
		dunnIndex = calculateDunnIndex(interDistance, intraDistance);
		cout << "The Dunn Index for a k of " << K << " is: " << dunnIndex << endl;
		if(dunnIndex > finalDunnIndex.kMeansDunnIndex)
		{
			finalDunnIndex.kMeansDunnIndex = dunnIndex;
			finalDunnIndex.kValue = K;
		}

	}

	//===================================================== END K-Means ==================================================================

	cout << endl;

	return finalDunnIndex;
}



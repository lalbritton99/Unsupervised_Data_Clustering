#include "filer.h"

map<int, point> reader(int *kMin, int *kMax, vector<vector<int>> *centroidNum){

	ifstream fin;
	string config, info, minCluster, maxCluster;
	vector<vector<string>> centroids;
	map<int, point> temp;

	//Checks that the entered configuration file exists
	while(true){
		cout << "Please enter the name of the configuration file: ";
		cin >> config;

		fin.open(config);
	
		if (!fin.is_open()){
			cout << endl;
			cout << "--- Configuration file " << config << " does not exist. Try Again ---" << endl;
			cout << endl;
		
		}
		else{ //Breaks if file is found
			break;
		}
	}

	//Store first line of config file
	fin >> info;
	fin.ignore();
	//store line with minimum cluster number
	getline(fin, minCluster);
	//store line with maximum cluster number
	getline(fin, maxCluster);

	while(fin){//stores the starting centroids for each k-means
		vector<int> tempVector;
		string tempo = "";
		int numTempo, num;
		fin >> tempo;
		tempo.pop_back();
		
		numTempo = atoi(tempo.c_str());
		tempVector.clear();
		for(int i = 0; i < numTempo; i++ ) {
			fin >> tempo;
			num = atoi(tempo.c_str());
			tempVector.push_back(num);
		}
			centroidNum->push_back(tempVector);
	}
	centroidNum->pop_back();
	fin.close();


	info = info.substr(6, info.size()-1); //Remove 'input:' from points file
		
	//Remove k-mean min: and k-mean max: from minimum and maximum cluster strings
	minCluster = minCluster.substr(11, minCluster.size()-1);
	maxCluster = maxCluster.substr(11, maxCluster.size()-1);

	
	//convert minimum and maximum cluster strings into integers
	*kMin = atoi(minCluster.c_str());
	*kMax = atoi(maxCluster.c_str());


	//check if points file exists, exits program if not found
	while(true){
                fin.open(info);

                if (!fin.is_open()){
                        cout << endl;
                        cout << "--- points file " << info << " does not exist." << endl << endl;
                        exit(EXIT_FAILURE);

                }
                else{ //Breaks if file is found
                        break;
                }
        }
	while(fin){ //Places points into point map
		point tempPoint;
		int index;
		fin >> index;
		fin >> tempPoint.x;
		fin >> tempPoint.y;
		tempPoint.ID = index;
		
		temp.emplace(index, tempPoint);
	}
	fin.close();

	return temp;
}

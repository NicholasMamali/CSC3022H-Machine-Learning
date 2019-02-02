

#include <math.h>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include<stdlib.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <limits>    
using namespace std; using namespace boost;

int main(int argc, char * argv[])
{
	ifstream myfile;
	string file = "input.txt";
  	myfile.open ((file).c_str(), ios::in|ios::binary);
  	if(!myfile){
  		cout<<"file could not be opened"<<endl;
  		exit(0);
  	}
  	
	vector<pair<pair<float,float>,int>> points;
	vector<pair<int,pair<pair<float,float>,vector<int>>>> clusters;
	string line;
	int clustNum=1;
	while(getline(myfile,line)){
		float x; float y; int n; int c =0;
		tokenizer<char_separator<char>> tokens(line);
		for (const auto& t : tokens) {
			if (c == 0){
				n = stoi((string)t);
			}
			else if (c == 1){
				x = stof((string)t);
			}
			else{
				y=stof((string)t);
			}c++;
		}
		
		if(n==7||n==1||n==4){clusters.push_back(make_pair(clustNum,make_pair(make_pair(x,y),vector<int>())));clustNum++;};
		points.push_back((make_pair(make_pair(x,y),n)));
	};

	myfile.close();
	ofstream outfile;
	outfile.open ("output.txt");
	
	bool changes = 0;
	int iterationNum = 1;
	while(!changes){
		changes = 1;
		for(auto& point: points){
			int closestClust;
			float distToClosest = numeric_limits<float>::max();
			for(auto& cluster: clusters){
				float distToCluster = pow(pow(point.first.first-cluster.second.first.first,2)+pow(point.first.second-cluster.second.first.second,2),0.5);
				if(distToCluster<=distToClosest){
					closestClust = cluster.first;
					distToClosest = distToCluster;
				}
			}
			for(auto& cluster: clusters){
				if(cluster.first==closestClust){
					bool found = 0;
					for(auto& Point: cluster.second.second){
						if(point.second==Point){
							//cout<<point.second<<endl;

							found = 1;
						}
					}
					if(found==0){
						changes = changes*0;
						cluster.second.second.push_back(point.second);
					}
				}
				else{
					int i = 0;
					for(auto& Point: cluster.second.second){
						if(point.second==Point){
							cluster.second.second.erase( cluster.second.second.begin() + i ); 
						}
						i++;
					}
				}

			}
		}
		for(auto& cluster: clusters){
		float sumX=0,sumY =0;
		for(auto& Point: cluster.second.second){
			for(auto& point: points){
				if(Point==point.second){
					sumX+=point.first.first;	sumY+=point.first.second;
				}
			}
		}
		cluster.second.first.first=sumX/(cluster.second.second.size());
		cluster.second.first.second=sumY/(cluster.second.second.size());
		}

		outfile << "Iteration " << iterationNum<<endl<<endl;
		
		for(auto& cluster: clusters){
			outfile<<"Cluster "<<cluster.first<<": ";//<<each->printPoints()<<std::endl;

			int j = 0;
			for(auto& Point: cluster.second.second){
				outfile<<Point;
				if(j!=(int)cluster.second.second.size()-1){
					outfile<<", ";
				}
				j++;
			}
			outfile<<endl<<"Centroid: ("<<cluster.second.first.first<<", "<<cluster.second.first.second<<")"<<endl<<endl;
			//num++;
		}
		iterationNum++;
	}
	cout<<"Answer = "<<iterationNum-1<<endl;
	outfile.close();


}
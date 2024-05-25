#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <bits/stdc++.h>
#include "entity.h"
#include "silhouette.h"
#include "cluster.h"
using namespace std;
/*
struct entity{
   int id;
   double value; 
   entity(int id, double value){
        this->id = id;
        this->value = value;
   }
};
*/
vector<double> k_mean_pp(vector<entity> dataset,int N);
vector<double> k_mean_step(vector<double> centroids, vector<entity> dataset,int N);
bool hasDifferent(vector<double> cent1 ,vector<double> cent2);
double minDist(entity point,vector<double> centroids);



int main(int argc, char* argv[])
{
    try
    {
        string IN = "";
        string OUT = "";
        string STAT = "";
        int N = 0;
        for (size_t i = 1; i < argc; i+=2){
            string key = *(argv+i);
            if(key.compare("-ifile")==0)
                IN = *(argv+i+1);
            if(key.compare("-ofile")==0)
                OUT = *(argv+i+1);
            if(key.compare("-stat")==0)
                STAT = *(argv+i+1);
            if(key.compare("-ncl")==0)
                N = stoi(*(argv+i+1));
        }
        if(IN.empty() || OUT.empty() || STAT.empty() || N<1){
            throw "invalid input";
        }   

        vector<entity> dataset = entity::loadDataSet(IN);

        vector<double> oldCentroids;
        vector<double> centroids = k_mean_pp(dataset,N);

        do{

            oldCentroids = centroids;
            centroids = k_mean_step(centroids,dataset,N);
        }while (hasDifferent(centroids, oldCentroids));

        vector<cluster> clusters = cluster::distributeIntoClusters(dataset,centroids);

        cluster::writeInFile(clusters, OUT);
        
        writeStat(clusters, STAT);

    }
    catch(const exception& e)
    {
        cerr <<"[ERROR] : "<< e.what() << endl;
        return 0;
    }
    return 1;
}

vector<double> k_mean_pp(vector<entity> dataset,int N){
    vector<double> centroids;
    
    centroids.push_back(
        dataset.at(
            rand() % dataset.size()
        ).value
    );

    while (centroids.size()<N)
    {
        double sumSquad = 0;
        for(entity point : dataset){
            double md = minDist(point, centroids);
            sumSquad+=md*md;
        }
        int r = rand() % (int)sumSquad;
        for(entity point : dataset){
            double md = minDist(point, centroids);
            sumSquad-= md*md;
            if(sumSquad<=0){
                centroids.push_back(point.value);
                break;
            }
        }
    }
    return centroids;

}

vector<double> k_mean_step(vector<double> centroids, vector<entity> dataset,int N){
    
    vector<cluster> clusters = cluster::distributeIntoClusters(dataset,centroids);

    //move centroids
    vector<double> newCentroids;
    for(cluster clust : clusters){
        double mean = 0;
        for(entity point : clust.content){
            mean+=point.value;
        }
        mean/=clust.size();
        newCentroids.push_back(mean);
    }
    return newCentroids;
}

double minDist(entity point, vector<double> centroids){
    double result = abs(point.value - centroids.at(0));
    for(double centr : centroids)
        result = min(result, abs(point.value - centr));
    return result;
}


bool hasDifferent(vector<double> cent1 ,vector<double> cent2){
    for(int i=0;i<cent1.size();i++){
        if(cent1.at(i)!=cent2.at(i)){
            return true;
        }
    }
    return false;
}



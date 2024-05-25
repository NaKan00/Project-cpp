#include "cluster.h"


void cluster::writeInFile(vector<cluster> clusters, string OUT){
    ofstream file(OUT); 
    for(int i=0;i<clusters.size();i++){
        file<<"cluster "<<i+1<<", ids:"<<endl;
        for(entity point : clusters.at(i).content){
            file<<point.id<<endl;
        }
    }
    cout<<"[INFO] write result [32msuccess[0m"<<endl;
}

void cluster::push_back(entity point){
    content.push_back(point);
}

int cluster::size(){
    return content.size();
}

int minDistIndex(entity point, vector<double> centroids){
    double result = abs(point.value - centroids.at(0));
    int index =0;
    for(int i=0;i<centroids.size();i++){
        double val = abs(point.value - centroids.at(i));
        if(result> val){
            result = val;
            index = i;
        }
    }
    return index;
}

vector<cluster> cluster::distributeIntoClusters(vector<entity> dataset, vector<double> centroids){
    vector<cluster> clusters;
    for(int i=0;i<centroids.size();i++){
        clusters.push_back(cluster());
    }
    for(entity point: dataset){
        clusters.at(minDistIndex(point, centroids)).push_back(point);
    }
    return clusters;
}
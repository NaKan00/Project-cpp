#ifndef CLUSTER_H
#define CLUSTER_H

#include "entity.h"

using namespace std;

class cluster{
    public:

    vector<entity> content;
    cluster(vector<entity> content){
        this->content = content;
    }

    cluster(){
        this->content = vector<entity>();
    }

    static void writeInFile(vector<cluster> clusters, string OUT);

    static vector<cluster> distributeIntoClusters(vector<entity> dataset, vector<double> centroids);

    static vector<double> k_mean_pp(vector<entity> dataset,int N);

    static double minDist(entity point, vector<double> centroids);

    static bool hasDifferent(vector<double> cent1 ,vector<double> cent2);

    void push_back(entity point);

    int size();
};

#endif
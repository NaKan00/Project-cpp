#ifndef CLUSTER_H
#define CLUSTER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
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
    void push_back(entity point);
    int size();
};
#endif
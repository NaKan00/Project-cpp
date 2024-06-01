#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class entity{
    public:

    int id;
    double value; 

    entity(int id, double value){
        this->id = id;
        this->value = value;
    }

    static vector<entity> loadDataSet(string IN);

};

#endif
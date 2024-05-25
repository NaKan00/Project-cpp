#include "entity.h"

using namespace std;
vector<entity> entity::loadDataSet(string IN) {
        ifstream file(IN); 
        vector<entity> dataset;
        if (!file.is_open()) 
            throw "Unable to open file (invalid ifile)!";  
    
        string line; 
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        while (getline(file, line)) { 
            stringstream ss = stringstream(line);

            string id;
            string val;

            getline(ss,  id, '\t');
            ss.ignore(numeric_limits<streamsize>::max(), '\t');
            ss.ignore(numeric_limits<streamsize>::max(), '\t');
            ss.ignore(numeric_limits<streamsize>::max(), '\t');
            getline(ss, val, '\t');

            if(val=="")
                continue;

            dataset.push_back(
                entity(
                    stoi(id),
                    (double)stoi(val)
                )
            );
        
        } 
        file.close(); 
        cout<<"[INFO] read file [32msuccess[0m"<<endl;
        return dataset;
    }
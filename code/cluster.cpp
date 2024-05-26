#include "cluster.h"


void cluster::writeInFile(vector<cluster> clusters, string OUT){
    ofstream file(OUT); 
    for(int i=0;i<clusters.size();i++){
        file<<"cluster "<<i+1<<", ids:"<<endl;
        for(entity point : clusters.at(i).content){
            file<<point.id<<endl;
        }
    }
    file.close();
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

vector<double> cluster::k_mean_pp(vector<entity> dataset,int N){
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
            double md = cluster::minDist(point, centroids);
            sumSquad+=md*md;
        }
        int r = rand() % (int)sumSquad;
        for(entity point : dataset){
            double md = cluster::minDist(point, centroids);
            r-= md*md;
            if(r<=0){
                centroids.push_back(point.value);
                break;
            }
        }
    }
    return centroids;

}



double cluster::minDist(entity point, vector<double> centroids){
    double result = abs(point.value - centroids.at(0));
    for(double centr : centroids)
        result = min(result, abs(point.value - centr));
    return result;
}


bool cluster::hasDifferent(vector<double> cent1 ,vector<double> cent2){
    for(int i=0;i<cent1.size();i++){
        if(cent1.at(i)!=cent2.at(i)){
            return true;
        }
    }
    return false;
}
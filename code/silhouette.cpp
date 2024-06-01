#include "silhouette.h"

using namespace std;


double a(cluster cluster, entity point, bool selfCluster){
    double sum = 0;
    for(entity other : cluster.content){
        sum+= abs(other.value - point.value);
    }
    return sum/(cluster.size()-selfCluster);
}

double b(vector<cluster>clusters, int indexCurrentCluster, entity point){
    vector<double> sums;
    for (int i = 0; i < clusters.size(); i++)
    {
        if(i==indexCurrentCluster)
            continue;
        sums.push_back(a(clusters.at(i), point,false));
    }
    return *max_element(sums.begin(), sums.end());
}

double s(vector<cluster>clusters, int indexCurrentCluster, entity point){
    double A = a(clusters.at(indexCurrentCluster),point, true);
    double B = b(clusters,indexCurrentCluster,point);
    return (B - A)/max(B, A);
}

double SC(vector<cluster> clusters, int indexCurrentCluster){
    cluster cluster = clusters.at(indexCurrentCluster);
    double sum = 0;
    for (int i = 0; i < cluster.size(); i++){
        sum+=s(clusters, indexCurrentCluster,cluster.content.at(i));
    }
    return sum / cluster.size();
}

void writeStat(vector<cluster> clusters, string STAT){
    ofstream file(STAT); 
    file<<"number of clusters:\t"<<clusters.size()<<endl;
    file<<"silhouette coefficient values:"<<endl;
    file<<setprecision(2);
    for(int i=0;i<clusters.size();i++){
        file<<"cluster "<<i+1<<":\t"<<SC(clusters,i)<<endl;
    }
    cout << fixed;
    file.close();
    cout<<"[INFO] write stats [32msuccess[0m"<<endl;
}
    
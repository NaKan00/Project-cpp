#include "entity.h"
#include "silhouette.h"
#include "cluster.h"
#include "parser.h"
using namespace std;

vector<double> k_mean_step(vector<double> centroids, vector<entity> dataset,int N);
vector<cluster> k_means(vector<entity> dataset,int N);

int main(int argc, char* argv[])
{
    try
    {
        auto keyWords = parseKeyWords(argc,argv);

        vector<entity> dataset = entity::loadDataSet(keyWords["ifile"]);

        vector<cluster> clusters = k_means(dataset, stoi(keyWords["ncl"]));

        cluster::writeInFile(clusters, keyWords["ofile"]);
        
        writeStat(clusters, keyWords["stat"]);

    }
    catch(const exception& e)
    {
        cerr <<"[ERROR] : "<< e.what() << endl;
        return 0;
    }
    return 1;
}


vector<cluster> k_means(vector<entity> dataset,int N){
        vector<double> oldCentroids;
        vector<double> centroids = cluster::k_mean_pp(dataset,N);

        do{
            oldCentroids = centroids;
            centroids = k_mean_step(centroids,dataset,N);
        }while (cluster::hasDifferent(centroids, oldCentroids));

        return cluster::distributeIntoClusters(dataset,centroids);
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





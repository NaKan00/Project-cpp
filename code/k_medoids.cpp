#include "entity.h"
#include "silhouette.h"
#include "cluster.h"
#include "parser.h"
using namespace std;

vector<double> k_medoid_step(vector<double> centroids, vector<entity> dataset,int N);
vector<cluster> k_medoids(vector<entity> dataset,int N);

int main(int argc, char* argv[])
{
    try
    {
        auto keyWords = parseKeyWords(argc,argv);

        vector<entity> dataset = entity::loadDataSet(keyWords["ifile"]);

        vector<cluster> clusters = k_medoids(dataset, stoi(keyWords["ncl"]));
        
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


vector<cluster> k_medoids(vector<entity> dataset,int N){
        vector<double> oldCentroids;
        vector<double> centroids = cluster::k_mean_pp(dataset,N);

        do{
            oldCentroids = centroids;
            centroids = k_medoid_step(centroids,dataset,N);
        }while (cluster::hasDifferent(centroids, oldCentroids));

        return cluster::distributeIntoClusters(dataset,centroids);
}

vector<double> k_medoid_step(vector<double> centroids, vector<entity> dataset,int N){
    
    vector<cluster> clusters = cluster::distributeIntoClusters(dataset,centroids);

    //move centroids
    vector<double> newCentroids;
    for(cluster clust : clusters){
        int grateCentroid = clust.content.at(0).value;
        double grateCentroidDistance = DBL_MAX;
        for (int i = 0; i < clust.size(); i++)
        {
            double centroid = clust.content.at(i).value;
            double sumDist = 0;
            for(entity point : clust.content)
                sumDist+=abs(point.value - centroid);
            if(sumDist<grateCentroidDistance){
                grateCentroid = centroid;
                grateCentroidDistance = sumDist;
            }
        }
        newCentroids.push_back(grateCentroid);
    }
    return newCentroids;
}





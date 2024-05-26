
#include "entity.h"
#include "silhouette.h"
#include "cluster.h"
#include "parser.h"
using namespace std;

vector<double> k_mean_step(vector<double> centroids, vector<entity> dataset,int N);

int main(int argc, char* argv[])
{
    try
    {
        auto keyWords = parseKeyWords(argc,argv);

        vector<entity> dataset = entity::loadDataSet(keyWords["ifile"]);

        vector<double> oldCentroids;
        vector<double> centroids = cluster::k_mean_pp(dataset,stoi(keyWords["ncl"]));

        do{

            oldCentroids = centroids;
            centroids = k_mean_step(centroids,dataset,stoi(keyWords["ncl"]));
        }while (cluster::hasDifferent(centroids, oldCentroids));

        vector<cluster> clusters = cluster::distributeIntoClusters(dataset,centroids);

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





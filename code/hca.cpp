#include "entity.h"
#include "silhouette.h"
#include "cluster.h"
#include "parser.h"
using namespace std;

vector<cluster> hca_step(vector<cluster> clusters);
vector<cluster> hca(vector<entity> dataset,int N);
double clusterWidth(cluster clust);
int getIndexSimilar(cluster clust);
double membershipLevel(entity point, cluster clust);

int main(int argc, char* argv[])
{
    try
    {
        auto keyWords = parseKeyWords(argc,argv);

        vector<entity> dataset = entity::loadDataSet(keyWords["ifile"]);

        vector<cluster> clusters = hca(dataset, stoi(keyWords["ncl"]));

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


vector<cluster> hca(vector<entity> dataset,int N){
        vector<cluster> clusters;
        clusters.push_back(cluster(dataset));
        while (clusters.size()!=N)
        {
            clusters = hca_step(clusters);
        }

        return clusters;
}

vector<cluster> hca_step(vector<cluster> clusters){
    
    int indexWidest = 0;
    double width = 0;
    for(int i=0;i<clusters.size();i++){
        double currentWidth = clusterWidth(clusters.at(i));
        if(currentWidth>width){
            width = currentWidth;
            indexWidest = i;
        }
    }

    cluster oldCluster = clusters.at(indexWidest);
    clusters.erase(clusters.begin()+indexWidest);
    cluster newCluster;

    while (oldCluster.size()!=0)
    {
        int similarIndex  = getIndexSimilar(oldCluster);
        entity point = oldCluster.content.at(similarIndex);
        oldCluster.content.erase(oldCluster.content.begin()+similarIndex);
        if(membershipLevel(point,oldCluster)<membershipLevel(point,newCluster)){
                oldCluster.push_back(point);
                break;
        }
        newCluster.push_back(point);

    }
    
    clusters.push_back(oldCluster);
    clusters.push_back(newCluster);

    return clusters;
}

double membershipLevel(entity point, cluster clust){
    double level = 0;
    for(entity clustPoint : clust.content){
        level+=abs(
            point.value - 
            clustPoint.value
        );
    }
    return level/clust.size();
}

double clusterWidth(cluster clust){
    double maxWidth = 0;
    for (int i = 0; i < clust.size(); i++){
        for (int j = 0; j < clust.size(); j++){
            maxWidth = max(
                maxWidth, 
                abs(
                    clust.content.at(i).value - 
                    clust.content.at(j).value
                )
            );
        }
    }
    return maxWidth;
}

int getIndexSimilar(cluster clust){
    int indexMaxMean=0;
    double maxMean=0;
    for (int i = 0; i < clust.size(); i++){
        double mean = 0;
        for (int j = 0; j < clust.size(); j++){
            mean+=abs(
                    clust.content.at(i).value - 
                    clust.content.at(j).value
            );
        }
        mean/=clust.size()-1;
        if(mean>maxMean){
            maxMean = mean;
            indexMaxMean = i;
        }
    }
    if(maxMean==0){
        throw "the specified number of clusters calculates the number of elements of the data set";
    }
    return indexMaxMean;
    
}




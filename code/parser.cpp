#include "parser.h"

using namespace std;

map<string, string> parseKeyWords(int argc, char* argv[]){
    map<string, string> keyWords
    {
        {"ifile", ""}, {"ofile", ""}, {"stat", ""}, {"ncl", ""}
    };
    for (size_t i = 1; i < argc; i+=2){
        string arg = *(argv+i);
        for (const auto& [key, val] : keyWords)
            if(arg.compare("-"+key)==0)
                keyWords[key] = *(argv+i+1);
    }
    for (const auto& [key, val] : keyWords)
        if(val.compare("")==0)
        throw "invalid input (has't key :"+key+")";
    if(stoi(keyWords["ncl"]) <1){
        throw "invalid input ( ncl ("+keyWords["ncl"]+") < 1)";
    }  
    return keyWords;
}
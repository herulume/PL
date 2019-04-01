#include "headers/graph.h"

#include<map>
#include<vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

Graph::Graph(){
}

vector<string> Graph::getTags(string tagss){
    vector<string> tags;
    istringstream iss(tagss);
    string token;
    while (std::getline(iss, token, ' ')){
        if(token.compare("and"))
            tags.push_back(token);
    }
    return tags;
}

void Graph::addCol(string pessoas){
    vector<string> autores = getTags(pessoas);

    switch(autores.size()){
        case 0:
            cout<< "ERROR" << endl;
            break;
        case 1:
            ++associacao[autores.front()][autores.front()];
            break;
        default:
            for (auto a : autores){
                for (auto b : autores){
                    if(a.compare(b)){
                        ++associacao[a][b];
                    }
                }
            }
            break;
    }
}

void Graph::addTag(vector<string>& tags){
    switch(tags.size()){
        case 0:
            cout<< "ERROR" << endl;
            break;

        case 1:
            ++associacao[tags.front()][tags.front()];
            break;

        default:
            for (auto a : tags){
                for (auto b : tags){
                    if(a.compare(b)){
                        ++associacao[a][b];
                    }
                }
            }
            break;
    }
}

bool Graph::isTag(string tag){
    return !(associacao.find(tag) == associacao.end());
}

void Graph::printTagG(string tag){
    string path = "./output/tags/";
    ofstream outfile;
    ostringstream os;
    ostringstream fileName;
    auto lista = associacao[tag];

    fileName << path << tag << ".dot";
    outfile.open(fileName.str());
    if(!outfile.is_open()) {
        std::cerr  << "Error creating dot file!" << std::endl;
        exit(1);
    }

    os << "strict graph {" << endl;
    for (auto it : lista) {
        os << setw(20) << "\"" << tag << "\""<<
            setw(20) << "--" << setw(20)
            << "\""<< it.first << "\"" << "[label=\""
            << it.second << "\","
            << "weight=\"" << it.second
            << "\"];" << endl;
    }
    os << "{rankdir=LR;}";
    os <<"}"<< endl;

    outfile << os.str();
    outfile.close();
}

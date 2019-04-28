#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<map>
#include<vector>

class Graph
{
        private:
                std::map<std::string, std::map<std::string, int>> associacao;
        public:
                Graph();
                std::vector<std::string> getTags(std::string);
                void addCol(std::string);
                bool isTag(std::string);
                void addTag(std::vector<std::string>&);
                void printTagG(std::string);
};
#endif

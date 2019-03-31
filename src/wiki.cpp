#include "headers/wiki.h"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

Wiki::Wiki(){}

Wiki::~Wiki(){
    for (auto& a : articles) {
        delete a;
    }
}

void Wiki::addArticle(Article* a){
    if(a != nullptr){
        this->articles.push_back(a);
    }
}

void Wiki::printArticles(){
    for (auto& a : articles) {
        a->toHTML();
    }
}

void Wiki::tagIndex(){
    std::string path = "./output/tags/";
    std::string rootPath = "./output/tagIndex.html";
    std::ostringstream rootOs;
    std::ofstream rootOutfile;

    rootOutfile.open(rootPath);
    if(!rootOutfile.is_open()) {
        std::cerr  << "Error creating HTML file!" << std::endl;
        exit(1);
    }

    std::unordered_map<std::string, std::vector<Article*>> articlesPerTag;
    for (auto& a : articles) {
        std::vector<std::string> tags = a->tags;
        for (auto t : tags) {
            auto it = articlesPerTag.find(t);
            if(it != articlesPerTag.end()){
                (it->second).push_back(a);
            } else {
                std::vector<Article*> articles;
                articlesPerTag[t] = articles;
                articlesPerTag[t].push_back(a);
            }
        }
    }

    rootOs << "<!DOCTYPE html>\n<html>\n\t<head><title>Tags!</title></head>\n\t<body><h1>Tags:</h1>\n\t\t<ul>";

    for (auto t : articlesPerTag){
        std::ofstream outfile;
        std::ostringstream os;
        std::ostringstream fileName;
        fileName << path << t.first << ".html";
        outfile.open(fileName.str());
        if(!outfile.is_open()) {
            std::cerr  << "Error creating HTML file!" << std::endl;
            continue;
        }
        os << "<!DOCTYPE html>\n<html>\n<head><title>" << t.first << "</title></head>\n<body><h1>Number of articles: " << t.second.size() << "</h1>\n\t<ul>" << std::endl;
        for(auto v : t.second)
            os << "<l1><a href=\"../articles/" << v->id << ".html\">" << v->title << "</a></l1>" << std::endl;
        os << "</ul></body></html>"<< std::endl;
        outfile << os.str();
        outfile.close();

        rootOs << "<li><a href=\"tags/" << t.first << ".html\">" << t.first << "</a></li>\n\t\t";
    }
        rootOs << "</ul>\n</body>\n</html>";
        rootOutfile << rootOs.str();
        rootOutfile.close();
}

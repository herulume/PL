#include "headers/wiki.h"
#include <vector>
#include <unordered_map>
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
    // TODO print stuff
    for (auto t : articlesPerTag){
        std::cout << "\nChave: " << t.first << " Valores: ";
        for(auto v : t.second)
            std::cout << v->title << " ";
    }
}

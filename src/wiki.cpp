#include "headers/wiki.h"

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
    for (auto& a : articles) {
        a->toHTML();
    }
}

#include "article.h"

Article::Article(std::string link){
    this -> link = link;
}

void Article::setId(std::string id) {
    this -> id = id;
}

void Article::setTitle(std::string title) {
    this -> title = title;
}

void Article::setAuthorDate(std::string authorDate) {
    this -> authorDate = authorDate;
}

void Article::addTag(std::string tag) {
    this -> tags.push_back(tag);
}

void Article::setCategory(std::string category) {
    this -> category = category;
}

void Article::setText(std::string text) {
    this -> text = text;
}

void Article::addAbbreviation(std::string abbreviation) {
    this -> abbreviations.push_back(abbreviation);
}


void Article::printer() {
    // file.open("../../html/1.html", ios_base::trunc);
    // file << "EU EXISTO!" << endl;
    printf("Ficheiro criado!!\n");
}
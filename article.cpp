#include "article.h"

Article::Article(string link){
    this -> link = link;
}

void Article::setId(string id) {
    this -> id = id;
}

void Article::setTitle(string title) {
    this -> title = title;
}

void Article::setAuthorDate(string authorDate) {
    this -> authorDate = authorDate;
}

void Article::addTag(string tag) {
    this -> tags.push_back(tag);
}

void Article::setCategory(string category) {
    this -> category = category;
}

void Article::setText(string text) {
    this -> text = text;
}

void Article::addAbbreviation(string abbreviation) {
    this -> abbreviations.push_back(abbreviation);
}


void Article::printer() {
    // file.open("../../html/1.html", ios_base::trunc);
    // file << "EU EXISTO!" << endl;
    printf("Ficheiro criado!!\n");
}
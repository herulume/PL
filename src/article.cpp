#include "headers/article.h"
#include <iostream>

Article::Article(std::string link){
    this->link = link;
}

void Article::setId(std::string id) {
    this->id = id;
}

void Article::setTitle(std::string title) {
    this->title = title;
}

void Article::setAuthorDate(std::string authorDate) {
    this->authorDate = authorDate;
}

void Article::addTag(std::string tag) {
    this->tags.push_back(tag);
}

void Article::setCategory(std::string category) {
    this->category = category;
}

void Article::setText(std::string text) {
    this->text = text;
}

void Article::addAbbreviation(std::string abbreviation) {
    this->abbreviations.push_back(abbreviation);
}


void Article::printer() {
    std::cout << "Link: " << this->link << std::endl;
    std::cout << "Title: " << this->title << std::endl;
    std::cout << "Id: " << this->id << std::endl;
    std::cout << "Author: " << this->authorDate << std::endl;
    std::cout << "Category: " << this->category << std::endl;
    std::cout << "Date: " << this->authorDate << std::endl;
    for (auto i = this->tags.begin(); i != this->tags.end(); ++i)
        std::cout << "Tag: "  << *i << std::endl;
    std::cout << "Text: " << this->text << std::endl;
}
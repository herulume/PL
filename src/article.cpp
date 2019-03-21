#include "headers/article.h"
#include <iostream>
#include <fstream>
#include <sstream>

Article::~Article() {
}

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
    std::cout << "Author_Date: " << this->authorDate << std::endl;
    std::cout << "Category: " << this->category << std::endl;
    for (auto i = this->tags.begin(); i != this->tags.end(); ++i)
        std::cout << "Tag: "  << *i << std::endl;
    std::cout << "Text: " << this->text << std::endl;
}


void Article::toHTML() {
    std::ofstream outfile;
    std::ostringstream os;
    std::ostringstream fileName;

    fileName << this->id << ".html";
    outfile.open(fileName.str());
    if(!outfile.is_open()) {
        std::cerr  << "Error creating HTML file!" << std::endl;
        exit(1);
    }

    os << "<pub id=\"" << this->id << "\">" << std::endl;
    os << "  <title>" << this->title << "</title>" << std::endl;
    os << "  <author_date>" << this->authorDate << "</author_date>" << std::endl;
    os << "  <tags>\n    ";
    for (auto i = this->tags.begin(); i != this->tags.end(); ++i) {
        os << "<tag>" << *i << "</tag>";
        if(i == this->tags.end()) os <<  " " << std::endl;
    }
    os << "\n  </tags>" << std::endl;
    os << "  <category>" << this->category << "</category>" << std::endl;
    os << "  <text>" << std::endl;
    os << this->text;
    os << "  </text>" << std::endl;
    os << "</pub>";


    outfile << os.str();
    outfile.close();
}

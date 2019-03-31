#include "headers/article.h"
#include <iostream>
#include <vector>
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

void Article::addText(std::string text) {
    this->text.push_back(text);
}

void Article::addAbbreviation(std::string abbreviation) {
    this->abbreviations.push_back(abbreviation);
}


void Article::toHTML() {
    std::string path = "./output/articles/";
    std::ofstream outfile;
    std::ostringstream os;
    std::ostringstream fileName;

    fileName << path << this->id << ".html";
    outfile.open(fileName.str());
    if(!outfile.is_open()) {
        std::cerr  << "Error creating HTML file!" << std::endl;
        exit(1);
    }

    os << "<!DOCTYPE html>\n<html>" << std::endl;

    os << "<head>\n<meta charset=\"utf-8\"/>\n\t";
    os << "<title>" << this->title << "</title>" << std::endl;
    os << "</head>" << std::endl;

    os << "<body>" << std::endl;
    os << "<meta charset=\"utf-8\"/>" << std::endl;
    os << "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans\" rel=\"stylesheet\">" << std::endl;
    os << "<link rel=\"stylesheet\" type=\"text/css\" href=\"styles/styles.css\">" << std::endl;
    os << "<pub id=\"" << this->id << "\">" << std::endl;
    os << "<div class=\"articles\">\n\t\t<h1 class=\"articles\"><u>";
    os << this-> title << "</u></h1>\n\t\t";
    os << "<ul>\n\t\t";
    os << "<li><small><author_date>" << this->authorDate << "</author_date></small></li>\n\n\t";
    os << "<li><small><category>Categoria: " << this->category << "</category></small></li>" << std::endl;
    os << "<li><small>Link original: " << this->link << "</small></li>\n\t";
    os << "</ul></div>\n\t\t";
    os << "\t<text>" << std::endl;

    int p = 1;
    for (auto t = this->text.begin(); t != this->text.end(); ++t) {
        int size = (*t).length();
        if(p) {
            os << "<p>";
            p = !p;
        }
        os << *t;
        if(size >= 2 && ((*t)[size-2]== '.')) {
            os << "</p>";
            p = !p;
        }
    }

    os << "\t</text>" << std::endl;
    os << "<h4>Tags:</h4>\n\t<tags><ul>\n\t\t";
    for (auto i = this->tags.begin(); i != this->tags.end(); ++i) {
        os << "<li><tag><a href=\"../tags/" << *i << ".html\">" << *i << "</a></tag></li>\n\t\t";
    }
    os << "\n\t</ul></tags>\n\t";

    if(this->abbreviations.size() > 0) {
        os << "<h4>Abbreviations:</h4>\n\t<ul>\n\t\t";
        for (auto i = this->abbreviations.begin(); i != this->abbreviations.end(); ++i) {
            os << "<li>" << *i << "</li>\n\t\t";
        }
        os << "\n\t</ul>\n\t";
    }
    os << "</pub>\n</body>\n</html>";


    outfile << os.str();
    outfile.close();
}

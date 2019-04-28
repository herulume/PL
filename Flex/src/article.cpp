#include "headers/article.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

Article::~Article()
{
}

Article::Article(std::string link)
{
        this->link = link;
}

void
Article::setId(std::string id)
{
        this->id = id;
}

void
Article::setTitle(std::string title)
{
        this->title = title;
}

void
Article::setAuthorDate(std::string authorDate)
{
        this->authorDate = authorDate;
}

void
Article::addTag(std::string tag)
{
        this->tags.push_back(tag);
}

void
Article::setCategory(std::string category)
{
        this->category = category;
}

void
Article::addText(std::string text)
{
        this->text.push_back(text);
}

void
Article::addAbbreviation(std::string abbreviation)
{
        this->abbreviations.push_back(abbreviation);
}


void
Article::toHTML()
{
        std::string path = "./output/articles/";
        std::ofstream outfile;
        std::ostringstream os;
        std::ostringstream fileName;
        fileName << path << this->id << ".html";
        outfile.open(fileName.str());

        if (!outfile.is_open()) {
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

                if (p) {
                        os << "<p>";
                        p = !p;
                }

                os << *t;

                if (size >= 2 && ((*t)[size - 2] == '.')) {
                        os << "</p>";
                        p = !p;
                }
        }

        os << "\t</text>" << std::endl;
        os << "<h4>Tags:</h4>\n\t<tags><ul>\n\t\t";

        for (auto i = this->tags.begin(); i != this->tags.end(); ++i)
                os << "<li><tag><a href=\"../tags/" << *i << ".html\">" << *i << "</a></tag></li>\n\t\t";

        os << "\n\t</ul></tags>\n\t";

        if (this->abbreviations.size() > 0) {
                os << "<h4>Abbreviations:</h4>\n\t<ul>\n\t\t";

                for (auto i = this->abbreviations.begin(); i != this->abbreviations.end(); ++i)
                        os << "<li>" << *i << "</li>\n\t\t";

                os << "\n\t</ul>\n\t";
        }

        os << "</pub>\n</body>\n</html>";
        outfile << os.str();
        outfile.close();
}


void
Article::toMarkdown()
{
        std::string path = "./output/articles/";
        std::ofstream outfile;
        std::ostringstream os;
        std::ostringstream fileName;
        fileName << path << this->id << ".md";
        outfile.open(fileName.str());

        if (!outfile.is_open()) {
                std::cerr  << "Error creating Markdown file!" << std::endl;
                exit(1);
        }

        os << "# " << this->title << std::endl << std::endl;
        os << "## Id" << std::endl << this->id << std::endl << std::endl;
        os << "## Title" << std::endl << this->title << std::endl << std::endl;
        os << "## Original Link" << std::endl << this->link << std::endl << std::endl;
        os << "## Author Date" << std::endl << this->authorDate << std::endl << std::endl;
        os << "## Tags" << std::endl;

        for (auto i = this->tags.begin(); i != this->tags.end(); ++i)
                os << "* " << *i << std::endl;

        os << std::endl;
        os << "## Text" << std::endl;
        int p = 1;

        for (auto t = this->text.begin(); t != this->text.end(); ++t) {
                int size = (*t).length();

                if (p)
                        p = !p;

                os << *t;

                if (size >= 2 && ((*t)[size - 2] == '.')) {
                        os << std::endl;
                        p = !p;
                }
        }

        os << std::endl;

        if (this->abbreviations.size() > 0) {
                os << "## Abbreviations" << std::endl;

                for (auto i = this->abbreviations.begin(); i != this->abbreviations.end(); ++i)
                        os << "* " << *i << std::endl;
        }

        outfile << os.str();
        outfile.close();
}

void
Article::toTex()
{
        std::string path = "./output/articles/";
        std::ofstream outfile;
        std::ostringstream os;
        std::ostringstream fileName;
        fileName << path << this->id << ".tex";
        outfile.open(fileName.str());

        if (!outfile.is_open()) {
                std::cerr  << "Error creating TeX file!" << std::endl;
                exit(1);
        }

        os << "\\documentclass[a4paper]{article}\n\\usepackage[pdftex]{hyperref}\n\\";
        os << "usepackage[utf8]{inputenc}\n\\begin{document}\n\\title{" << this->title << "}" << std::endl;
        os << "\\maketitle\n\\author{" << this->authorDate << "}\n\\setcounter{tocdepth}{1}\n\\tableofcontents\n\n\\newpage" << std::endl;
        os << "\\section{Id}\n" << this->id << std::endl;
        os << "\\section{Original link}\n" << this->link << std::endl;
        os << "\\section{Category}\n" << this->category << std::endl;
        os << "\\section{Tags}\n" << std::endl;
        os << "\\begin{itemize}" << std::endl;

        for (auto i = this->tags.begin(); i != this->tags.end(); ++i)
                os << "\\item " << *i << std::endl;

        os << "\\end{itemize}" << std::endl;
        os << std::endl;
        os << "\\section{Text}\n" << std::endl;

        for (auto t = this->text.begin(); t != this->text.end(); ++t)
                os << *t;

        os << std::endl;

        if (this->abbreviations.size() > 0) {
                os << "\\section{Abbreviations}\n" << std::endl;
                os << "\\begin{itemize}" << std::endl;

                for (auto i = this->abbreviations.begin(); i != this->abbreviations.end(); ++i)
                        os << "\\item " << *i << std::endl;

                os << "\\end{itemize}" << std::endl;
        }

        os << "\\end{document}\n";
        outfile << os.str();
        outfile.close();
}

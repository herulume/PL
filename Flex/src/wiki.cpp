#include "headers/wiki.h"
#include "headers/graph.h"
#include <vector>
#include <unordered_map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>

Wiki::Wiki() {}

Wiki::~Wiki()
{
        for (auto& a : articles)
                delete a;
}

void
Wiki::addArticle(Article* a)
{
        if (a != nullptr)
                this->articles.push_back(a);
}



void
Wiki::printAll()
{
        this->printArticles();
        this->printArticlesMD();
        this->printArticlesTex();
        this->titleIndex();
        this->tagIndex();
        this->index();
}

void
Wiki::printArticles()
{
        for (auto& a : articles)
                a->toHTML();
}

void
Wiki::printArticlesMD()
{
        for (auto& a : articles)
                a->toMarkdown();
}

void
Wiki::printArticlesTex()
{
        for (auto& a : articles)
                a->toTex();
}

void
Wiki::index()
{
        std::string rootPath = "./output/index.html";
        std::ostringstream rootOs;
        std::ofstream rootOutfile;
        rootOutfile.open(rootPath);

        if (!rootOutfile.is_open()) {
                std::cerr  << "Error creating HTML file!" << std::endl;
                exit(1);
        }

        rootOs << "<!DOCTYPE html>\n<html>\n\t<head><title>Articles!</title></head>\n\t";
        rootOs << "<body>";
        rootOs << "<h1><pre>" << "   _____          __  .__       .__                 \n";
        rootOs << "  /  _  \\________/  |_|__| ____ |  |   ____   ______\n";
        rootOs << " /  /_\\  \\_  __ \\   __\\  |/ ___\\|  | _/ __ \\ /  ___/\n";
        rootOs << "/    |    \\  | \\/|  | |  \\  \\___|  |_\\  ___/ \\___ \\ \n";
        rootOs << "\\____|__  /__|   |__| |__|\\___  >____/\\___  >____  >\n";
        rootOs << "        \\/                    \\/          \\/     \\/ \n";
        rootOs << "</pre></h1>\n";
        rootOs << "<h2><a href=\"titleIndex.html\">Articles per title</a></h2>\n";
        rootOs << "<h2><a href=\"tagIndex.html\">Articles per tag</a></h2>";
        rootOs << "</body></html>";
        rootOutfile << rootOs.str();
        rootOutfile.close();
}

void
Wiki::generateGraphs(Graph* g)
{
        std::set<std::string> tags;

        for (auto a : this->articles) {
                for (auto t : a->tags)
                        tags.insert(t);
        }

        for (auto t : tags)
                g->printTagG(t);
}

void
Wiki::titleIndex()
{
        std::string rootPath = "./output/titleIndex.html";
        std::ostringstream rootOs;
        std::ofstream rootOutfile;
        rootOutfile.open(rootPath);

        if (!rootOutfile.is_open()) {
                std::cerr  << "Error creating HTML file!" << std::endl;
                exit(1);
        }

        rootOs << "<!DOCTYPE html>\n<html>\n\t<head><title>Articles!</title></head>\n\t<body><h1>Articles:</h1>\n\t\t<ul>";

        for (auto t : this->articles)
                rootOs << "<li><a href=\"articles/" << t->id << ".html\">" << t->title << "</a></li>\n\t\t";

        rootOs << "</ul>\n</body>\n</html>";
        rootOutfile << rootOs.str();
        rootOutfile.close();
}

void
Wiki::tagIndex()
{
        std::string path = "./output/tags/";
        std::string rootPath = "./output/tagIndex.html";
        std::ostringstream rootOs;
        std::ofstream rootOutfile;
        rootOutfile.open(rootPath);

        if (!rootOutfile.is_open()) {
                std::cerr  << "Error creating HTML file!" << std::endl;
                exit(1);
        }

        std::unordered_map<std::string, std::vector<Article*>> articlesPerTag;

        for (auto& a : articles) {
                std::vector<std::string> tags = a->tags;

                for (auto t : tags) {
                        auto it = articlesPerTag.find(t);

                        if (it != articlesPerTag.end())
                                (it->second).push_back(a);

                        else {
                                std::vector<Article*> articles;
                                articlesPerTag[t] = articles;
                                articlesPerTag[t].push_back(a);
                        }
                }
        }

        rootOs << "<!DOCTYPE html>\n<html>\n\t<head><title>Tags!</title></head>\n\t<body><h1>Tags:</h1>\n\t\t<ul>";

        for (auto t : articlesPerTag) {
                std::ofstream outfile;
                std::ostringstream os;
                std::ostringstream fileName;
                fileName << path << t.first << ".html";
                outfile.open(fileName.str());

                if (!outfile.is_open()) {
                        std::cerr  << "Error creating HTML file!" << std::endl;
                        continue;
                }

                os << "<!DOCTYPE html>\n<html>\n<head><title>" << t.first << "</title></head>\n<body><h1>Number of articles: " << t.second.size() << "</h1>\n<h2>Articles:</h2>\n\t<ul>" << std::endl;

                for (auto v : t.second)
                        os << "<l1><a href=\"../articles/" << v->id << ".html\">" << v->title << "</a></l1>" << std::endl;

                os << "</ul>" << std::endl;
                os << "<img src=\"" << t.first << ".dot.png\" alt=\"" << t.first << "Graph\" >\n</body></html>" << std::endl;
                outfile << os.str();
                outfile.close();
                rootOs << "<li><a href=\"tags/" << t.first << ".html\">" << t.first << "</a></li>\n\t\t";
        }

        rootOs << "</ul>\n</body>\n</html>";
        rootOutfile << rootOs.str();
        rootOutfile.close();
}


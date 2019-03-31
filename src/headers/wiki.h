#ifndef __WIKI_H__
#define __WIKI_H__

#include <vector>
#include "article.h"
#include "graph.h"

class Wiki {
    public:
        Wiki();
        ~Wiki();
        std::vector<Article*> articles;
        void index();
        void printAll();
        void tagIndex();
        void titleIndex();
        void printArticles();
        void printArticlesMD();
        void printArticlesTex();
        void addArticle(Article*);
        void generateGraphs(Graph*);
};

#endif

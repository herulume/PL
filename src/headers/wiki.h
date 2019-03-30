#ifndef __WIKI_H__
#define __WIKI_H__

#include <vector>
#include "article.h"

class Wiki {
    public:
        Wiki();
        ~Wiki();
        std::vector<Article*> articles;
        void tagIndex();
        void printArticles();
        void addArticle(Article*);

};

#endif

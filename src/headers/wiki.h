#ifndef __WIKI_H__
#define __WIKI_H__

#include <vector>
#include <unordered_map>
#include "article.h"

class Wiki {
    public:
        Wiki();
        ~Wiki();
        std::vector<Article*> articles;
        std::unordered_map<std::string, std::vector<Article*>> articlesPerTag;
        void tagIndex();
        void printArticles();
        void addArticle(Article*);

};

#endif

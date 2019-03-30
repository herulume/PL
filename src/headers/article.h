#ifndef __ARTICLE_H__
#define __ARTICLE_H__

#include <vector>
#include <string>

class Article {
    public:
        std::string file;
        std::string link;
        std::string id;
        std::string title;
        std::string authorDate;
        std::vector<std::string> tags;
        std::string category;
        std::vector<std::string> text;
        std::vector<std::string> abbreviations;
        Article(std::string link);
        ~Article();
        void setId(std::string id);
        void setTitle(std::string title);
        void setAuthorDate(std::string AuthorDate);
        void addTag(std::string tag);
        void setCategory(std::string category);
        void addText(std::string text);
        void addAbbreviation(std::string abbreviation);
        void toHTML();
};

#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <cstring>
#include <string.h>
#include <stdexcept>
#include <stdio.h>

using namespace std;

class Article {
  private:
    ofstream file;
    void htmlStart();
    void htmlEnd();
  public:
    string link;
    int id;
    string title;
    string authorDate;
    vector<string> tags;
    string category;
    vector <string> text;
    vector <string> abbreviations;

    void setId(int id);
    void setTitle(string title);
    void setAuthorDate(string AuthorDate);
    void addTag(string tag);
    void setCategory(string category);
    void addText(string text);
    void addAbbreviation(string abbreviation);
    Article(string link);
    void printer();
};
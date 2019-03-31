%option c++
%option noyywrap
%{
#include "headers/article.h"
#include "headers/wiki.h"
#include "headers/graph.h"
#include "string.h"
#include <string>
#include <vector>
std::string last;
std::vector<std::string> tags;
Graph* g {new Graph};
Wiki* articles {new Wiki};
Article* article;
%}

%x LINK
%x TAG
%x ID
%x CATEGORIA
%x TITULO
%x TEXTO
%x AUTHOR_DATE

word    ([a-zA-Z]+)
marks   (à|á|â|ã|é|è|ê|ẽ|í|ì|î|ĩ|ó|ò|ô|õ|ú|ù|û|ũ)
wordPT  ({word}+{marks}*{word}*)
silence (.|\n)

floatN  ([0-9]+\.[0-9]+)
intN    ([0-9]+)
number  ({floatN}|{intN})


%%
<INITIAL>{
"<!--"" "+"="+" "?                 { BEGIN LINK;        }
(?i:tag)":{"                       { BEGIN TAG;         }
"#"(?i:ID)":{"                     { BEGIN ID;          }
({wordPT}("-"{wordPT})?[ ]?)+"}\n" { BEGIN CATEGORIA;   }
"#DATE:".+"] "                     { BEGIN AUTHOR_DATE; }
}


<LINK>{
[^ ]+             { article = new Article(yytext); }
[ ]+"-->"" "*"\n" { BEGIN INITIAL;                 }
}

<AUTHOR_DATE>{
.+                     { article->setAuthorDate(yytext); }
"\n"("[".*"]""\n")?    { BEGIN TEXTO;                    }
}

<TAG>{
[^"}"]+ { article->addTag(yytext); tags.push_back(yytext);}
"}"     { BEGIN INITIAL;           }
}

<ID>{
[^ ]+ { article->setId(yytext); }
[ ]   { BEGIN INITIAL;          }
}

<CATEGORIA>{
.+ { article->setCategory(yytext); }
"\n"+    { BEGIN TITULO;                 }
}

<TITULO>{
.+ { article->setTitle(yytext); }
"\n"                                { BEGIN INITIAL;             }
}

<TEXTO>{
"\n"+((?i:Etiquetas).+)?"\n</pub>"   { articles->addArticle(article); g->addTag(tags); tags.clear(); BEGIN INITIAL; }

({wordPT}" "?){2,}." "*"("[A-Z]{2,}(.[A-Z]+)*")"  { article->addAbbreviation(yytext); }

.+\n                       {  if(last.compare(yytext)) article->addText(yytext); yymore(); last = yytext; REJECT; }
}

<*>{silence}

%%
int main(int argc, char** argv) {
    FlexLexer* lexer = new yyFlexLexer;

    if(argc == 2 && (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))){
        std::cout << argv[0] << " <flags>  < input_file" << std::endl;
        exit(0);
    }

    lexer->yylex();

    if(argc == 2 && (!strcmp(argv[1], "--markdown") || !strcmp(argv[1], "-m"))) {
        articles->printAll();
        articles->generateGraphs(g);
    } else {
        articles->printArticles();
        articles->titleIndex();
        articles->tagIndex();
        articles->index();
        articles->generateGraphs(g);
    }

    delete lexer;
    delete articles;
    return 0;
}

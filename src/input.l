%option c++
%option noyywrap
%{
#include "headers/article.h"
#include <vector>
std::vector<Article*> articles;
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
"<!--"[ ]+"="+                 { BEGIN LINK;       }
"tag:{"                        { BEGIN TAG;        }
"#ID:{"                        { BEGIN ID;         }
({word}("-"{word})?[ ]?)+"}\n" { BEGIN CATEGORIA;  }
"#DATE:".+"] "                 { BEGIN AUTHOR_DATE;}
}


<LINK>{
[^ ]+|^"-->"      { article = new Article(yytext); }
[ ]+"-->"[ ]*"\n" { BEGIN INITIAL;                 }
}

<AUTHOR_DATE>{
.+|^"\n" { article->setAuthorDate(yytext);
           BEGIN TEXTO;
         }
}

<TAG>{
[^"}"]+ { article->addTag(yytext); }
"}"     { BEGIN INITIAL;           }
}

<ID>{
[^ ]+ { article->setId(yytext); }
[ ]   { BEGIN INITIAL;          }
}

<CATEGORIA>{
{wordPT} { article->setCategory(yytext); }
"\n"+    { BEGIN TITULO;                 }
}

<TITULO>{
(({number}|{wordPT})[ ]*)+ { article->setTitle(yytext); }
"\n"                                { BEGIN INITIAL;             }
}

<TEXTO>{
(.+"\n""\n"?)+ { article->setText(yytext);
                 articles.push_back(article);
                 BEGIN INITIAL;
               }
}

<*>{silence}

%%
int main() {
    FlexLexer* lexer = new yyFlexLexer;
    lexer->yylex();
    for (auto& a : articles) {
        a->toHTML();
        delete a;
    }
    delete lexer;
    return 0;
}

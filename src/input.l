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
"<!--"" "+"="+" "?                 { BEGIN LINK;       }
(?i:tag)":{"                       { BEGIN TAG;        }
"#"(?i:ID)":{"                     { BEGIN ID;         }
({wordPT}("-"{wordPT})?[ ]?)+"}\n" { BEGIN CATEGORIA;  }
"#DATE:".+"] "                     { BEGIN AUTHOR_DATE;}
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
[^"}"]+ { article->addTag(yytext); }
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
"\n"+((?i:Etiquetas).+)?"\n</pub>"   { BEGIN INITIAL; }
(.+"\n""\n"?)+                       { article->setText(yytext);
                                       articles.push_back(article);
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

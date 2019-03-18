%option c++
%option noyywrap
%{
#include "article.h"
#include <iostream> 
#include <stdio.h>
Article* article;
FlexLexer* lexer = new yyFlexLexer;
%}

%x ARTICLE
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

%%
<INITIAL>{
"<!--"[ ]+"="+                 { BEGIN LINK;      }
"tag:{"                        { BEGIN TAG;       }
"#ID:{"                        { BEGIN ID;        }
({word}("-"{word})?[ ]?)+"}\n" { BEGIN CATEGORIA; }
"[".*"]""\n"+                  { BEGIN TEXTO;     }
"#DATE:".+"] "           { BEGIN AUTHOR_DATE;}
}


<ARTICLE>{
"<pub>" {printf("COMECEI!\n"); BEGIN INITIAL;}
"\n</pub>" {article->printer(), printf("Acabei!\n");BEGIN INITIAL;}
}

<AUTHOR_DATE>{
.+|^"\n" { article -> setAuthorDate(yytext); std::cout << "AUTHOR_DATE: " << article->authorDate << '\n'; BEGIN INITIAL;}
}

<LINK>{
[^ ]+|^"-->"           { article = new Article(yytext);         std::cout << "LINK: " << article->link << '\n'; }
[ ]+"-->"[ ]*"\n" { BEGIN ARTICLE;       }
}

<TAG>{
[^"}"]+ { article -> addTag(yytext); std::cout << "TAG: " << article->tags[1] << '\n';}
"}"     { BEGIN INITIAL;               }
}

<ID>{
[^ ]+ { article -> setId(yytext); std::cout << "ID: " << article->id << '\n';}
[ ]   { BEGIN INITIAL;              }
}

<CATEGORIA>{
{wordPT} { article -> setCategory(yytext); std::cout << "CATEGORY: " << article->category << '\n'; }
"\n"+    { BEGIN TITULO;                      }
}

<TITULO>{
(([0-9]*|{wordPT})[ ]*)+ { article -> setTitle(yytext); std::cout << "TITLE: " << article->title << '\n';  }
"\n"                     { BEGIN INITIAL;                  }
}

<TEXTO>{
(.+"\n""\n"?)+ {
    yytext[yyleng-1] = '\0';
    article -> setText(yytext); std::cout << "TEXT: " << article->text << '\n';;
}
^\n(\n+).* { BEGIN INITIAL; }
}

<*>{silence}
%%
int yywrap() { return 1; }

int main() {
    FlexLexer* lexer = new yyFlexLexer;
    lexer -> yylex();
    return 0;
}

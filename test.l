%option c++
%option noyywrap
%{
#include "article.h"
#include <iostream> 
#include <stdio.h>
vector<Article*> articles;
FlexLexer* lexer = new yyFlexLexer;
%}

%x ARTICLE
%x LINK
%x TAG
%x ID
%x CATEGORIA
%x TITULO
%x TEXTO

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
}

<ARTICLE>{
"<pub>" {printf("COMECEI!\n"); BEGIN INITIAL;}
"\n</pub>" {printf("Acabei!\n");BEGIN INITIAL;}
}

<LINK>{
[^ ]+|^"-->"           { printf("Link: %s\n", yytext); }
[ ]+"-->"[ ]*"\n" { BEGIN ARTICLE;       }
}

<TAG>{
[^"}"]+ { printf("Tag: %s\n", yytext); }
"}"     { BEGIN INITIAL;               }
}

<ID>{
[^ ]+ { printf("ID: %s\n", yytext); }
[ ]   { BEGIN INITIAL;              }
}

<CATEGORIA>{
{wordPT} { printf("Categoria: %s\n", yytext); }
"\n"+    { BEGIN TITULO;                      }
}

<TITULO>{
(([0-9]*|{wordPT})[ ]*)+ { printf("Titulo: %s\n", yytext); }
"\n"                     { BEGIN INITIAL;                  }
}

<TEXTO>{
(.+"\n""\n"?)+ {
    yytext[yyleng-1] = '\0';
    printf("Texto: %s\n", yytext);
}
^\n(\n+).* { BEGIN ARTICLE; }
}

<*>{silence}
%%
int yywrap() { return 1; }

int main() {
    FlexLexer* lexer = new yyFlexLexer;
    lexer -> yylex();
    return 0;
}

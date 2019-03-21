%option c++
%option noyywrap
%{
#include "headers/article.h"
Article* article;
FlexLexer* lexer = new yyFlexLexer;
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

%%
<INITIAL>{
"<!--"[ ]+"="+                 { BEGIN LINK;      }
"tag:{"                        { BEGIN TAG;       }
"#ID:{"                        { BEGIN ID;        }
({word}("-"{word})?[ ]?)+"}\n" { BEGIN CATEGORIA; }
"[".*"]""\n"+                  { BEGIN TEXTO;     }
"#DATE:".+"] "                 { BEGIN AUTHOR_DATE;}
}


<LINK>{
[^ ]+|^"-->"      { article = new Article(yytext); }
[ ]+"-->"[ ]*"\n" { BEGIN INITIAL;                 }
}

<AUTHOR_DATE>{
.+|^"\n" { article->setAuthorDate(yytext);
           BEGIN INITIAL;
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
(([0-9]*|{wordPT})[ ]*)+ { article->setTitle(yytext); }
"\n"                     { BEGIN INITIAL;             }
}

<TEXTO>{
(.+"\n""\n"?)+ { article->setText(yytext);          }
^\n(\n+).*     { BEGIN INITIAL; article->printer(); }
}

<*>{silence}

%%
int yywrap() { return 1; }
int main() {
    FlexLexer* lexer = new yyFlexLexer;
    lexer->yylex();
    return 0;
}

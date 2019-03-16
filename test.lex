%{
#include <stdio.h>
%}

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

<LINK>{
[^ ]+|^"-->"           { printf("Link: %s\n", yytext); }
[ ]+"-->"[ ]*"\n<pub>" { BEGIN INITIAL;       }
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
([^"\n"]+"\n""\n"?)+ {
    yytext[yyleng-1] = '\0';
    printf("Texto: %s\n<lol>", yytext);
}
^\n(\n+).*"\n</pub>" { BEGIN INITIAL; }
}

<*>{silence}
%%
int yywrap() { return 1; }

int main() {
    yylex();
    return 0;
}

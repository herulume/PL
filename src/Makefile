CFLAGS = -Wall -Wextra -O2 -march=native -std=c++11

ifeq ($(OS),Windows_NT)
	@echo "Doesn't run on Windoze."
	exit
endif

detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
ifeq ($(detected_OS),Darwin)
	CFLAGS += -ll
else
	CLAGS += -lfl
endif


articles: input.l article.o
	@mkdir ../bin
	@flex --noyywrap --c++ input.l
	$(CXX) $(CFLAGS) lex.yy.cc article.o -o ../bin/articles
	@rm lex.yy.cc article.o

article.o:
	$(CXX) -c article.cpp $(CFLAGS)

clean:
	@rm -rf ../bin lex.yy.cc *.o 2>/dev/null || true

install:
	@cp ../bin/articles /usr/bin
	@cp ../bin/articles /usr/local/bin

remove:
	@rm /usr/bin/articles
	@rm /usr/local/bin/articles
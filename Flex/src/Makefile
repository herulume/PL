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


articles: input.l article.o wiki.o graph.o directory.o
	@mkdir -p ../bin/output/articles
	@mkdir ../bin/output/tags
	@cp -R ../styles ../bin/output/articles
	@flex --noyywrap --c++ input.l
	$(CXX) $(CFLAGS) lex.yy.cc directory.o article.o wiki.o graph.o -o ../bin/articles
	@rm lex.yy.cc article.o

wiki.o:
	$(CXX) -c wiki.cpp $(CFLAGS)

article.o:
	$(CXX) -c article.cpp $(CFLAGS)

graph.o:
	$(CXX) -c graph.cpp $(CFLAGS)

directory.o:
	$(CXX) -c directory.c $(CFLAGS)

clean:
	@rm -rf ../bin lex.yy.cc *.o 2>/dev/null || true

install: articles.l
	@cp ../bin/articles /usr/bin
	@cp ../bin/articles /usr/local/bin
	@cp articles.l a.l
	@gzip a.l
	@cp a.l.gz /usr/share/man/man1/articles.1.gz
	@mandb
	@rm a.l.gz
remove:
	@rm /usr/bin/articles
	@rm /usr/local/bin/articles
	@rm /usr/share/man/man1/articles.1.gz
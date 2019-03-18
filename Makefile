CFLAGS = -Wall -Wextra -O2 -march=native -std=c++11

ifeq ($(OS),Windows_NT)
	@echo "You need a proper OS!"
	exit
endif

detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
ifeq ($(detected_OS),Darwin)
	CFLAGS += -ll
else
	CFLAGS += -lfl
endif


articles: test.l article.o
	@mkdir build
	@flex --noyywrap --c++ test.l
	$(CXX) $(CFLAGS) lex.yy.cc article.o -o articles
	@rm lex.yy.cc article.o
	@mv articles build/

article.o:
	$(CXX) -c article.cpp -std=c++11

clean:
	@rm -rf build lex.yy.cc *.o 2>/dev/null || true
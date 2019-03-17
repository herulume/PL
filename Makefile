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


articles: test.l
	@mkdir build
	@flex --noyywrap --c++ test.l
	$(CXX) $(CFLAGS) lex.yy.cc -o articles
	@rm lex.yy.cc
	@mv articles build/


clean:
	@rm -rf build lex.yy.cc *.o 2>/dev/null || true
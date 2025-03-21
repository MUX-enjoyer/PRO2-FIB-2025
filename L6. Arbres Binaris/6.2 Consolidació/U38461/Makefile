CXX := g++
CXXFLAGS := -g3 -D_GLIBCXX_DEBUG -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program: *.cc
	$(CXX) $(CXXFLAGS) -o program *.cc

clean:
	rm -f program

.PHONY: clean

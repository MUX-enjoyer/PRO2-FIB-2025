CXX := g++
CXXFLAGS := -g3 -std=c++11 -D_GLIBCXX_DEBUG -Wall -Wextra -Werror -Wno-sign-compare -fno-extended-identifiers

program: *.cc
	$(CXX) $(CXXFLAGS) -o program *.cc

clean:
	rm -f program

.PHONY: clean

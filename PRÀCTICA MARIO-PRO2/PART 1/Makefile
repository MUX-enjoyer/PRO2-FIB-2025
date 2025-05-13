CXX = g++
CXXFLAGS = -std=c++17
ifeq "$(MODE)" "release"
CXXFLAGS += -O3
else
CXXFLAGS += -g3
endif

# Afegim llibreries segons el sistema operatiu
ifeq ($(OS),Windows_NT)
    LDFLAGS += -lgdi32
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LDFLAGS += -lX11
    endif
    ifeq ($(UNAME_S),Darwin)
        LDFLAGS += -framework Cocoa
    endif
endif

CCFILES := $(wildcard *.cc)
HHFILES := $(wildcard *.hh)
OBJS := $(patsubst %.cc,%.o,$(CCFILES))
TAR_FILE = mario-pro-2-$(USER)-$(shell date +%s).tgz

mario_pro_2: $(OBJS)
	g++ -g3 -o mario_pro_2 $(OBJS) $(LDFLAGS)

$(OBJS): $(HHFILES)
window.o: window.cc geometry.hh fenster.h

tgz: clean
	tar -czf $(TAR_FILE) Makefile *.cc *.hh fenster.h .vscode .clang-format

clean:
	rm -f mario_pro_2 $(OBJS)

.PHONY: clean tgz

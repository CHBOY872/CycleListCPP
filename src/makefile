CPP=g++
CPPFLAGS=-Wall -ansi -g

SRCMODULES=$(shell find . -name '*.cpp' | grep -v 'main.cpp')
OBJMODULES=$(SRCMODULES:.cpp=.o)
HEDMODULES=$(SRCMODULES:.cpp=.hpp)

%.o: %.cpp %.hpp
	$(CPP) $(CPPFLAGS) $< -c -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(CPPSRCMODULES) $(CSRCMODULES)
	$(CC) -MM $^ > $@

main: main.cpp $(OBJMODULES)
	$(CPP) $(CPPFLAGS) $^ -o $@

clean:
	find . -name '*.o' -delete

all:
	make main
	make clean

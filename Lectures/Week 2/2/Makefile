CXX = g++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror
LDLIBS += -lstdc++ -lm

Out.txt : main # $< er input, måske kun det første, og $@ er target
	./$< > $@

main.o:

main: main.o
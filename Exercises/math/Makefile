CXXFLAGS = -Wall -Werror -Wextra -std=c++23 -O
LDLIBS = -lstdc++ -lm

Out.txt: main
	./$< > $@

main: main.o sfuns.o
	$(CXX) $^ -o $@ $(LDLIBS)

sfuns.o : sfuns.h sfuns.cc
	$(CXX) $(CXXFLAGS) -o sfuns.o -c sfuns.cc
main.o : sfuns.h main.cc
	$(CXX) $(CXXFLAGS) -o main.o -c main.cc

clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o

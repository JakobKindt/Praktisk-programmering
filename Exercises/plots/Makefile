CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm

Out.txt: main
	./$< > $@

fig1.svg: fig1.gpi erf.data
	gnuplot $<

main: main.o sfuns.o
	$(CXX) $^ -o $@ $(LDLIBS)

sfuns.o: sfuns.h sfuns.cc
	$(CXX) $(CXXFLAGS) -o sfuns.o -c sfuns.cc

main.o: sfuns.h main.cc
	$(CXX) $(CXXFLAGS) -o main.o -c main.cc

erf.data: main Makefile
	./$< -xmin 0.125 -xmax 4 -dx 0.0125 > $@ 2>log.erf

clean: 
	$(RM) main main.o Out.txt *.o
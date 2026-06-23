CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

all: Out.txt fig_times.svg

Out.txt : main
	./main > Out.txt 


main : main.o matrix.o vector.o PSO.o

main.o : main.cc vector.h matrix.h PSO.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.h matrix.cc vector.h vector.o

PSO : PSO.o matrix.o vector.o

PSO.o : PSO.h PSO.cc vector.h matrix.h

fig_times.svg : times.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "Amount of particles" ;\
	set ylabel "Time to converge [ms]" ;\
	set title "Investigation of time dependence for PSO" ;\
	plot \
		"$<" using 1:2 with points ;\
	'|tee log.fig_times|gnuplot


.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier times.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 

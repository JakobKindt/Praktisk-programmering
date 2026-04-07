CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

all: Out.txt fig_acc.svg

Out.txt : main
	./main > Out.txt 


main : main.o QUAD.o

main.o : main.cc QUAD.h vector.h

vector : vector.O

vector.o : vector.h vector.cc

QUAD : QUAD.o

QUAD.o : QUAD.h QUAD.cc

fig_acc.svg : acc.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set title "Influence of accuracy when evaluating erf(1)" ;\
	set xlabel "acc" ;\
	set ylabel "abs(measured - theoretical) of erf(1)" ;\
	set logscale xy ;\
	plot \
		"$<" using 1:3 with linespoints title "" ;\
	' |tee log.fig_acc|gnuplot

.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
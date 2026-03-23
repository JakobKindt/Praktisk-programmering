CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link


all: Out.txt fig_pend.svg fig_lot.svg

Out.txt : main
	./main > Out.txt 


main : main.o matrix.o ODE.o vector.o

main.o : main.cc vector.h matrix.h ODE.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.cc matrix.h vector.h vector.o

ODE : ODE.o matrix.o vector.o

ODE.o : matrix.h vector.h ODE.h ODE.cc


fig_pend.svg: pend.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	set title "Pendulum with friction" ;\
	plot \
		"$<" using 1:2 with lines title "b = 0.3, c = 7. MAKE NEW LABEL" ;\
	' |tee log.pend |gnuplot


fig_lot.svg: lot.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	set title "Pendulum with friction" ;\
	plot \
		"$<" using 1:2 with lines title "y_0. a = 1.5, b = 1. MAKE NEW LABEL" ,\
		"$<" using 1:3 with lines title "y_1. c = 3, d = 1. MAKE NEW LABEL" ;\
	' |tee log.pend |gnuplot



.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 

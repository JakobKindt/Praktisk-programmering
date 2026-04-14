CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

all: Out.txt fig_err.svg fig_ints.svg fig_quasi_err.svg fig_quasi_ints.svg

Out.txt : main
	./main > Out.txt 


main : main.o MC.o matrix.o vector.o

main.o : main.cc MC.h vector.h matrix.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.h matrix.cc vector.h vector.o

MC : MC.o matrix.o vector.o

MC.o : MC.h MC.cc matrix.h vector.h

fig_err.svg: err.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set title "Error of integral of cos(theta) for 0 <= theta <= pi/2, 0 < r < 1 via MC" ;\
	set xlabel "Amount of sample datapoints" ;\
	set ylabel "err of integral" ;\
	set logscale x ;\
	a = 1 ;\
	f(x) = a/sqrt(x) ;\
	fit f(x) "$<" using 1:4 via a ;\
	plot \
		"$<" using 1:3 with points title "Measured error", \
		"$<" using 1:4 with points title "Actual error", \
		f(x) with lines title sprintf("Fit to a/sqrt(N) fit, a = %3.5f", a);\
	' |tee log.err|gnuplot


fig_ints.svg: err.txt Makefile
	echo ' \
	set terminal svg ;\
	set output "$@" ;\
	set title "Value of integral of cos(theta) for 0 <= theta <= pi/2, 0 < r < 1 via MC. Theoretical is 1." ;\
	set xlabel "Amount of sample datapoints" ;\
	set ylabel "Value of integral" ;\
	set logscale x ;\
	f(x) = pi ;\
	plot \
		"$<" using 1:2 with points title "Interal value", \
		f(x) with lines dashtype 2 linecolor rgb "#000000" title "Theoretical" ;\
	' |tee log.ints|gnuplot


fig_quasi_err.svg: quasi_err.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set title "Error of integral of cos(theta) for 0 <= theta <= pi/2, 0 < r < 1 via MC" ;\
	set xlabel "Amount of sample datapoints" ;\
	set ylabel "err of integral" ;\
	set logscale x ;\
	a = 1 ;\
	f(x) = a/sqrt(x) ;\
	fit f(x) "$<" using 1:4 via a ;\
	plot \
		"$<" using 1:3 with points title "Measured error", \
		"$<" using 1:4 with points title "Actual error", \
		f(x) with lines title sprintf("Fit to a/sqrt(N) fit, a = %3.5f", a) ;\
	' |tee log.quasi_err|gnuplot

fig_quasi_ints.svg: quasi_err.txt Makefile
	echo ' \
	set terminal svg ;\
	set output "$@" ;\
	set title "Value of integral of cos(theta) for 0 <= theta <= pi/2, 0 < r < 1 via MC. Theoretical is 1." ;\
	set xlabel "Amount of sample datapoints" ;\
	set ylabel "Value of integral" ;\
	set logscale x ;\
	f(x) = pi ;\
	plot \
		"$<" using 1:2 with points title "Interal value", \
		f(x) with lines dashtype 2 linecolor rgb "#000000" title "Theoretical" ;\
	' |tee log.quasi_ints|gnuplot

.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

all: Out.txt fig_wave_func.svg fig_conv_acc.svg fig_conv_eps.svg fig_conv_rmin.svg fig_conv_rmax.svg

Out.txt : main
	./main > Out.txt 


main : main.o Root.o matrix.o vector.o QR-factorization.o ODE.o

main.o : main.cc Root.h vector.h matrix.h QR-factorization.h ODE.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.h matrix.cc vector.h vector.o

Root : Root.o matrix.o vector.o QR-factorization.o

Root.o : Root.h Root.cc matrix.h vector.h QR-factorization.h

QR-factorization : QR-factorization.o matrix.o vector.o

QR-factorization.o : QR-factorization.cc QR-factorization.h matrix.h vector.h

ODE : ODE.o matrix.o vector.o

ODE.o : ODE.cc ODE.h matrix.h vector.h

fig_wave_func.svg: wave_func.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set title "Solution to radial SE for hydrogen" ;\
	set xlabel "r" ;\
	set ylabel "wave function" ;\
	f(x) = x*exp(-x) ;\
	plot \
		"$<" using 1:2 with lines title "Estimated solution", \
		f(x) with lines title "Theoretical solution" ;\
	'|tee log.wave_func|gnuplot


fig_conv_acc.svg: conv_acc.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set title "Solution to radial SE for hydrogen - Investigation of influence of acc" ;\
	set xlabel "r" ;\
	set ylabel "wave function" ;\
	f(x) = x*exp(-x) ;\
	plot \
		"$<" using 1:2 index 0 with lines title "acc = 1e-5", \
		"$<" using 1:2 index 1 with lines title "acc = 1e-3", \
		"$<" using 1:2 index 2 with lines title "acc = 1e-2", \
		"$<" using 1:2 index 3 with lines title "acc = 1e-1", \
		f(x) with lines dashtype 2 linecolor rgb "#000000" title "Theoretical solution" ;\
	'|tee log.wave_func|gnuplot

fig_conv_eps.svg: conv_eps.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set title "Solution to radial SE for hydrogen - Investigation of influence of eps" ;\
	set xlabel "r" ;\
	set ylabel "wave function" ;\
	f(x) = x*exp(-x) ;\
	plot \
		"$<" using 1:2 index 0 with lines title "eps = 1e-5", \
		"$<" using 1:2 index 1 with lines title "eps = 1e-3", \
		"$<" using 1:2 index 2 with lines title "eps = 1e-2", \
		"$<" using 1:2 index 3 with lines title "eps = 1e-1", \
		f(x) with lines dashtype 2 linecolor rgb "#000000" title "Theoretical solution" ;\
	'|tee log.wave_func|gnuplot

fig_conv_rmin.svg: conv_rmin.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set title "Solution to radial SE for hydrogen - Investigation of influence of rmin" ;\
	set xlabel "r" ;\
	set ylabel "wave function" ;\
	f(x) = x*exp(-x) ;\
	plot \
		"$<" using 1:2 index 0 with lines title "rmin = 1e-5", \
		"$<" using 1:2 index 1 with lines title "rmin = 1e-3", \
		"$<" using 1:2 index 2 with lines title "rmin = 1e-2", \
		"$<" using 1:2 index 3 with lines title "rmin = 1e-1", \
		f(x) with lines dashtype 2 linecolor rgb "#000000" title "Theoretical solution" ;\
	'|tee log.wave_func|gnuplot

fig_conv_rmax.svg: conv_rmax.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set title "Solution to radial SE for hydrogen - Investigation of influence of rmax" ;\
	set xlabel "r" ;\
	set ylabel "wave function" ;\
	f(x) = x*exp(-x) ;\
	plot \
		"$<" using 1:2 index 0 with lines title "rmax = 1", \
		"$<" using 1:2 index 1 with lines title "rmax = 3", \
		"$<" using 1:2 index 2 with lines title "rmax = 5", \
		"$<" using 1:2 index 3 with lines title "rmax = 10", \
		f(x) with lines dashtype 2 linecolor rgb "#000000" title "Theoretical solution" ;\
	'|tee log.wave_func|gnuplot


.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
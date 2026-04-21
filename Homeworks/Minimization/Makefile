CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

all: Out.txt fig_exp_fit.svg

Out.txt : main
	./main > Out.txt 


main : main.o min.o matrix.o vector.o QR-factorization.o

main.o : main.cc min.h vector.h matrix.h QR-factorization.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.h matrix.cc vector.h vector.o

min : min.o matrix.o vector.o QR-factorization.o

min.o : min.h min.cc matrix.h vector.h QR-factorization.h

QR-factorization : QR-factorization.o matrix.o vector.o

QR-factorization.o : QR-factorization.cc QR-factorization.h matrix.h vector.h


fig_exp_fit.svg : exp_data.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "Energy [GeV]" ;\
	set ylabel "Signal [Arbitrary units]" ;\
	m = 125.972; gamma = 2.0864; A = 9.87649 ;\
	f(x) = A/((x - m)*(x - m) + gamma*gamma/4) ;\
	plot \
		"$<" using 1:2:3 with yerrorbars title "Data", \
		f(x) with lines title "Fit using minimization" ;\
	'|tee log.fig_exp_fit|gnuplot

.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
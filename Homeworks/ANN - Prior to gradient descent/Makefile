CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

all: Out.txt fig_fit.svg

Out.txt : main
	./main > Out.txt 


main : main.o min.o matrix.o vector.o QR-factorization.o ANN.o

main.o : main.cc min.h vector.h matrix.h QR-factorization.h ANN.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.h matrix.cc vector.h vector.o

ANN : ANN.o matrix.o vector.o min.o QR-factorization.o

ANN.o : ANN.h ANN.cc vector.h matrix.h QR-factorization.h ANN.h

min : min.o matrix.o vector.o QR-factorization.o

min.o : min.h min.cc matrix.h vector.h QR-factorization.h

QR-factorization : QR-factorization.o matrix.o vector.o

QR-factorization.o : QR-factorization.cc QR-factorization.h matrix.h vector.h

fig_fit.svg : data.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	set title "neurons = FIX" ;\
	f(x) = cos(5*x - 1) * exp(-x*x) ;\
	plot \
		"$<" using 1:2 with lines title "Fit", \
		"$<" using 1:3 with lines title "Calculated values", \
		f(x) with lines title "Theoretical cos(5*x - 1) * exp(-x*x)" ;\
	'|tee log.fig_fit|gnuplot

.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
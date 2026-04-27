CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

all: Out.txt fig_fit.svg fig_fitb.svg fig_fit_antiderivative.svg

Out.txt : main
	./main > Out.txt 


main : main.o matrix.o vector.o ANN.o

main.o : main.cc vector.h matrix.h ANN.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.h matrix.cc vector.h vector.o

ANN : ANN.o matrix.o vector.o

ANN.o : ANN.h ANN.cc vector.h matrix.h

fig_fit.svg : data.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	set title "4 neurons fit to cos(5*x - 1) * exp(-x*x)" ;\
	f(x) = cos(5*x - 1) * exp(-x*x) ;\
	plot \
		"$<" using 1:2 index 0 with lines title "Fit", \
		"$<" using 1:2 index 1 with points title "Trainng data", \
		f(x) with lines title "Analytical f(x)" ;\
	'|tee log.fig_fit|gnuplot

fig_fitb.svg : data.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	set title "4 neurons fit to cos(5*x - 1) * exp(-x*x)" ;\
	f(x) = cos(5*x - 1) * exp(-x*x) ;\
	df(x) = -5*sin(5*x - 1)*exp(-x*x) - 2*x*f(x) ;\
	ddf(x) = -25*cos(5*x - 1)*exp(-x*x) + 20*x*sin(5*x - 1)*exp(-x*x) + (4*x*x - 2)*f(x) ;\
	plot \
		"$<" using 1:2 index 0 with lines title "Fit to f", \
		"$<" using 1:3 index 0 with lines title "Fit to F", \
		"$<" using 1:4 index 0 with lines title "Fit to df/dx", \
		"$<" using 1:5 index 0 with lines title "Fit to d^2f/dx^2", \
		f(x) with lines title "Analytical f(x)", \
		df(x) with lines title "Analytical df/dx", \
		ddf(x) with lines title "Analytical d^2f/dx^2" ;\
	'|tee log.fig_fit|gnuplot

fig_fit_antiderivative.svg : data.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	set title "4 neurons fit to cos(5*x - 1) * exp(-x*x). Too complex analytical F(x) to implement" ;\
	f(x) = cos(5*x - 1) * exp(-x*x) ;\
	df(x) = -5*sin(5*x - 1)*exp(-x*x) - 2*x*f(x) ;\
	ddf(x) = -25*cos(5*x - 1)*exp(-x*x) + 20*x*sin(5*x - 1)*exp(-x*x) + (4*x*x - 2)*f(x) ;\
	plot \
		"$<" using 1:2 index 0 with lines title "Fit to f", \
		"$<" using 1:3 index 0 with lines title "Fit to F", \
		f(x) with lines title "Analytical f(x)" ;\
	'|tee log.fig_fit|gnuplot

.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
# CXXFLAGS = -Wall -Wextra -std=c++23 -O
# LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
# LDLIBS = -lstdc++ -lm #L is for link

# all: Out.txt fig_fit.svg

# Out.txt : main
# 	./main > Out.txt 


# main : main.o min.o matrix.o vector.o QR-factorization.o ANN.o

# main.o : main.cc min.h vector.h matrix.h QR-factorization.h ANN.h

# vector : vector.o

# vector.o : vector.h vector.cc

# matrix : matrix.o vector.o

# matrix.o : matrix.h matrix.cc vector.h vector.o

# ANN : ANN.o matrix.o vector.o min.o QR-factorization.o

# ANN.o : ANN.h ANN.cc vector.h matrix.h QR-factorization.h ANN.h

# min : min.o matrix.o vector.o QR-factorization.o

# min.o : min.h min.cc matrix.h vector.h QR-factorization.h

# QR-factorization : QR-factorization.o matrix.o vector.o

# QR-factorization.o : QR-factorization.cc QR-factorization.h matrix.h vector.h

# fig_fit.svg : data.txt Makefile
# 	echo '\
# 	set terminal svg ;\
# 	set output "$@" ;\
# 	set xlabel "x" ;\
# 	set ylabel "y" ;\
# 	set title "neurons = FIX" ;\
# 	f(x) = cos(5*x - 1) * exp(-x*x) ;\
# 	plot \
# 		"$<" using 1:2 with lines title "Fit", \
# 		"$<" using 1:3 with lines title "Calculated values", \
# 		f(x) with lines title "Theoretical cos(5*x - 1) * exp(-x*x)" ;\
# 	'|tee log.fig_fit|gnuplot

# .PHONY:clean 
# clean: # Forces to remove the stuff listed
# 	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

# test:
# 	@echo CXX
# 	@echo $(CXX)
# 	@echo $(RM) 
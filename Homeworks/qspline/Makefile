CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link


all: Out.txt Splines_lin.svg Splines_quad.svg

Out.txt : main
	./main > Out.txt 

Splines_lin.svg: data_a.txt Makefile
	echo ' \
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "x" ;\
		set ylabel "y" ;\
		set title "Fitting using Spline" ;\
		set key outside;\
		f(x) = cos(x) ;\
		F(x) = sin(x) ;\
		plot \
			f(x) with lines lt rgb "black" title "f(x) = cos(x)", \
			F(x) with lines lt rgb "black" title "F(x) = sin(x)", \
			"$<" using 4:5 with points title "Data", \
			"$<" using 1:2 with lines title "f(x) via Spline", \
			"$<" using 1:3 with lines title "F(x) via Spline" ;\
	' |tee log.activities |gnuplot

Splines_quad.svg: data_b.txt Makefile
	echo ' \
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "x" ;\
		set ylabel "y" ;\
		set title "Fitting using Spline" ;\
		set key outside;\
		f(x) = cos(x) ;\
		F(x) = sin(x) ;\
		plot \
			f(x) with lines lt rgb "black" title "f(x) = cos(x)", \
			F(x) with lines lt rgb "black" title "F(x) = sin(x)", \
			"$<" using 4:5 with points title "Data", \
			"$<" using 1:2 with lines title "f(x) via Spline", \
			"$<" using 1:3 with lines title "F(x) via Spline" ;\
	' |tee log.activities |gnuplot



main : main.o matrix.o Splines.o vector.o

main.o : main.cc vector.h matrix.h Splines.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.cc matrix.h vector.h vector.o

Splines : Splines.o matrix.o vector.o

Splines.o : matrix.h vector.h Splines.h Splines.cc



.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 

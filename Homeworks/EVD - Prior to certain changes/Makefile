CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link


all: Out.txt out.dr.txt out.rmax.txt dr.svg rmax.svg out.func.txt func.svg

Out.txt : main
	./main > Out.txt 

out.func.txt: main
	./$< -dr 0.01 -rmax 10 -output $@ 1 >> $@

out.dr.txt : main
	for dr in $$(seq 0.05 0.05 1); do \
		echo "$$dr $$(./$< -dr $$dr -make_dr 1)" >> $@;\
	done

out.rmax.txt : main
	for rmax in $$(seq 1 1 10); do \
		echo "$$rmax $$(./$< -rmax $$rmax -make_rmax 1)" >> $@ ;\
	done

	

dr.svg: out.dr.txt
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "dr" ;\
		set ylabel "Lowest eigenvalue" ;\
		plot \
			"$<" using 1:2 with linespoints title "Investigation of eigenvalues" ;\
		' | tee log.times | gnuplot

rmax.svg: out.rmax.txt
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "rmax" ;\
		set ylabel "Lowest eigenvalue" ;\
		plot \
			"$<" using 1:2 with linespoints title "Investigation of eigenvalues" ;\
		' | tee log.times | gnuplot

func.svg: out.func.txt
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "r" ;\
		set ylabel "Wavefunction" ;\
		plot \
			"$<" using 1:2 with lines title "f_1", \
			"$<" using 1:3 with lines title "f_2", \
			"$<" using 1:4 with lines title "f_3", \
			"$<" using 1:5 with lines title "f_4" \
		' | tee log.times |gnuplot

main : main.o matrix.o EVD.o

main.o : main.cc vec.h matrix.h EVD.h

matrix : matrix.o

matrix.o : matrix.cc matrix.h vec.h EVD.h

EVD : EVD.o matrix.o

EVD.o : matrix.h vec.h EVD.h EVD.cc

Ns := $(shell seq 100 10 500)
out.times-2.txt: main.cc Makefile
	for N in $(Ns); do \
		time -ao log.$$N -f "$$N %e" ./$< -size $$N & \
	done; wait
	>$@
	for N in $(Ns); do cat log.$$N >> $@; done
	$(RM) log*


times.svg: out.times-2.txt
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "Dimension of random matrix" ;\
		set ylabel "Real time (s)" ;\
		set title "Time for EVD" ;\
		a = 1; b = 1; c = 1; d = 1 ;\
		f(x) = a*x*x*x + b*x*x + c*x + d ;\
		fit f(x) "$<" using 1:2 via a,b,c,d ;\
		plot \
			"$<" using 1:2 with linespoints title "Data", \
			f(x) with lines title "fit as O(n^3)" ;\
		' | tee log.times | gnuplot


.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 

CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

all: Out.txt fig_times.svg fig_convergence.svg

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

fig_times.svg : data.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "Amount of particles" ;\
	set ylabel "Time to converge [ms]" ;\
	set title "Investigation of time dependence for PSO" ;\
	a = 1 ;\
	b = 1 ;\
	c = 1 ;\
	d = 1 ;\
	f(x) = a*x + b ;\
	g(x) = c*x**d ;\
	fit f(x) "$<" using 1:2 via a, b ;\
	fit g(x) "$<" using 1:2 via c, d ;\
	plot \
		"$<" using 1:2 with points title "Data", \
		f(x) with lines dt 2 lc rgb "#000000" title sprintf("Fit to ax + b, a = %3.5f, b = %3.5f", a, b), \
		g(x) with lines dt 2 lc rgb "#0015ff" title sprintf("Fit to cx^d, c = %3.5f, d = %3.5f", c, d) ;\
	'|tee log.fig_times|gnuplot


fig_convergence.svg : data.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "Amount of particles" ;\
	set ylabel "Amount of steps to converge" ;\
	set title "Investigation of convergence for PSO" ;\
	plot \
		"$<" using 1:3 with points title "data" ;\
	'|tee log.fig_convergence|gnuplot

# fig_convergence.svg : data.txt Makefile
# 	echo '\
# 	set terminal svg ;\
# 	set output "$@" ;\
# 	set xlabel "Amount of particles" ;\
# 	set ylabel "Amount of steps to converge" ;\
# 	set title "Investigation of convergence for PSO" ;\
# 	a = 1 ;\
# 	b = 1 ;\
# 	f(x) = a/x + b ;\
# 	fit f(x) "$<" using 1:3 via a, b ;\
# 	plot \
# 		"$<" using 1:3 with points title "data", \
# 		f(x) with lines title sprintf("Fit to a/x + b, a = %3.5f, b = %3.5f", a, b) ;\
# 	'|tee log.fig_convergence|gnuplot

# fig_convergence.svg : data.txt Makefile
# 	echo '\
# 	set terminal svg ;\
# 	set output "$@" ;\
# 	set xlabel "Amount of particles" ;\
# 	set ylabel "Amount of steps to converge" ;\
# 	set title "Investigation of convergence for PSO" ;\
# 	plot \
# 		"$<" using 1:3 with points title "data", \
# 	'|tee log.fig_convergence|gnuplot


.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier times.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 

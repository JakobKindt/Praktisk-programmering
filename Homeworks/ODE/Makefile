CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link


all: Out.txt fig_pend.svg fig_lot.svg fig_orbit.svg fig_stable_orbit.svg

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
		"$<" using 1:2 with lines title "theta'\'''\''(t) + 0.3 theta'\''(t) + 7 sin(theta(t)) = 0 (b = 0.3, c = 7)" ;\
	' |tee log.pend |gnuplot

fig_lot.svg: lot.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	set title "Pendulum with friction" ;\
	plot \
		"$<" using 1:2 with lines title "x for x'\'' = 1.5x + xy (a = 1.5, b = 1)" ,\
		"$<" using 1:3 with lines title "y for y'\'' = -3y + xy (c = 3, d = 1)" ;\
	' |tee log.pend |gnuplot


fig_orbit.svg: orbit.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	set title "Orbits" ;\
	plot \
		"$<" index 0 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines title "eps = 0, u'\''(0) = 0",  \
		"$<" index 1 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines title "eps = 0, u'\''(0) = -0.5", \
		"$<" index 2 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines dt 2 title "eps = 0.01, u'\''(0) = -0.5" ;\
	' |tee log.orbit |gnuplot


fig_stable_orbit.svg: stable_orbit.txt Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	set title "Stable Orbits" ;\
	plot \
		"$<" using 2:3 with lines title "Planet 1",  \
		"$<" using 4:5 with lines title "Planet 2", \
		"$<" using 6:7 with lines lc rgb(0, 0, 0) title "Planet 3" ;\
	' |tee log.stable_orbit |gnuplot


.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
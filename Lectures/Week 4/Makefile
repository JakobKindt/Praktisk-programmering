CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm

all: fig1.svg fig2.png fig3.svg

test.txt: erf.data Makefile #This will make a new file containing only column 1 and 2.
	>$@
	cat erf.data | while read a b c; do echo $$a $$b >> $@; done

# fig3.svg: test.txt Makefile
# 	graph --output-format svg $< > $@
fig3.svg: test.txt Makefile
	graph \
		--x-label "x" \
		--y-label "y" \
		--output-format svg \
		$< > $@


fig1.svg: fig1.gpi erf.data
	gnuplot $<

fig2.png: erf.data Makefile
	echo '\
	set terminal png ;\
	set output "$@" ;\
	set tics out ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	plot [][-2:2]\
		 "$<" index 0 using 1:2 with linespoints \
		,"$<" index 0 using 1:3 with lines \
	' | tee log.fig2.pgi | gnuplot

erf.data : main Makefile # $@ is the target
	./$< -xmin -2 -xmax 2 -dx 0.5 > $@ 2>log.erf
	echo "\n\n" >> $@
	./$< -xmin -0 -xmax 10 -dx 0.25 > $@ 2>log.erf

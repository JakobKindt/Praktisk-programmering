CXXFLAGS += -std=c++23 -Wall -O
LDLIBS += -lstdc++ -lm -lpthread
TIME = time --append --output $@ --format "$$nthreads %e %U"

times.svg: out.times Makefile
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "Number of threads" ;\
		set ylabel "Real time (s)" ;\
		a = 1; b = 10;\
		f(x) = a + b/x \;
		fit f(x) using 1:2 via a,b ;\
		plot \
			"$<" using 1:2 with lineplots title "Times" \
			, f(x) title "fit with 1/n" ;\
	'| tee log.times |gnuplot

times.svg: out.times Makefile
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "number of threads" ;\
		set ylabel "real time" ;\
		a=1; b=10;\
		f(x)=a+b/x;\
		fit f(x) "$<" using 1:2 via a,b ;\
		plot \
			 "$<" using 1:2 with linespoints title "times" \
			 ,f(x) title "fit with 1/n" ;\
	'| tee log.times |gnuplot


N = 1e9
out.times: main Makefile
	>$@
	>log.main
	for nthreads in $$(seq 100); \
		do $(TIME) ./main -terms $(N) -threads $$nthreads >> log.main ;\
	done

clean:
	$(RM) log* [Oo]ut* main *.svg fit.log
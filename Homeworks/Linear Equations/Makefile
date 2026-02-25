CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

Out.txt : main
	./main > Out.txt 

out.times.data : main
	>$@
	for N in $$(seq 20 20 500); do \
		time --format "$$N %e" --output $@ --append ./main -size $(N) $$N >> log.main ;\
	done


times.svg: out.times.data
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "Dimension of square matrix" ;\
		set ylabel "Real time (s)" ;\
		a = 1; b = 1; c = 1; d = 1; \
		f(x) = a*x*x*x + b*x*x + c*x + d ;\
		fit f(x) "$<" using 1:2 via a,b,c,d ;\
		plot \
			"$<" using 1:2 with linespoints title "Investigation of time" \
			, f(x) with lines title "fit with third order polynomial" ;\
		' | tee log.times | gnuplot

# times.svg: out.times.data
# 	echo '\
# 		set terminal svg ;\
# 		set output "$@" ;\
# 		set xlabel "Dimension of square matrix" ;\
# 		set ylabel "Real time (s)" ;\
# 		a = 1; b = 1; c = 1; d = 1; \
# 		f(x) = a*x*x*x + b*x*x + c*x + d ;\
# 		fit f(x) "$<" using 1:2 via a,b,c,d ;\
# 		plot \
# 			"$<" using 1:2 with linespoints title "Investigation of time", \
# 			f(x) with lines title "fit with third order polynomial" ;\
# 		' | tee log.times | gnuplot

# times.svg: out.times Makefile
# 	echo '\
# 		set terminal svg ;\
# 		set output "$@" ;\
# 		set xlabel "Number of threads" ;\
# 		set ylabel "Real time (s)" ;\
# 		a = 1; b = 10;\
# 		f(x) = a + b/x \;
# 		fit f(x) using 1:2 via a,b ;\
# 		plot \
# 			"$<" using 1:2 with lineplots title "Times" \
# 			, f(x) title "fit with 1/n" ;\
# 	'| tee log.times |gnuplot


main : main.o matrix.o QR-factorization.o 

main.o : main.cc vec.h matrix.h QR-factorization.h

matrix : matrix.o

matrix.o : matrix.cc matrix.h vec.h QR-factorization.h

QR-factorization : QR-factorization.o

QR-factorization.o : matrix.h vec.h

.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 

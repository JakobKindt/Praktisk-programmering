CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link


all: Out.txt fig_lin.svg fig_exp.svg

Out.txt : main
	./main > Out.txt 


fig_lin.svg: data.txt fitting_parameters.txt Makefile
	echo ' \
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "Time (days)" ;\
		set ylabel "ln(Activity)" ;\
		set title "Fitting using OLS via QR" ;\
		a = real(system("awk '\''NR==1{print $$1}'\'' $(word 2,$^)")) ;\
		b = real(system("awk '\''NR==2{print $$1}'\'' $(word 2,$^)")) ;\
		aerr = real(system("awk '\''NR==1{print $$2}'\'' $(word 2,$^)")) ;\
		berr = real(system("awk '\''NR==2{print $$2}'\'' $(word 2,$^)")) ;\
		f(x) = a - b*x ;\
		g(x) = a - aerr - (b + berr)*x ;\
		h(x) = a + aerr - (b - berr)*x ;\
		plot \
			"$<" using 1:4:5 with errorbars title "data", \
			f(x) with lines lt rgb "black" title sprintf("Fit using ln(a) - b*x, ln(a)=%.3f, b = %.3f", a, b), \
			g(x) with lines dashtype 2 lt rgb "black" title "Uncertainty band", \
			h(x) with lines dashtype 2 lt rgb "black" title "" ;\
	' |tee log.activities |gnuplot

fig_exp.svg: data.txt fitting_parameters.txt Makefile
	echo ' \
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "Time (days)" ;\
		set ylabel "Activity" ;\
		set title "Fitting using OLS via QR" ;\
		a = real(system("awk '\''NR==1{print $$1}'\'' $(word 2,$^)")) ;\
		b = real(system("awk '\''NR==2{print $$1}'\'' $(word 2,$^)")) ;\
		aerr = real(system("awk '\''NR==1{print $$2}'\'' $(word 2,$^)")) ;\
		berr = real(system("awk '\''NR==2{print $$2}'\'' $(word 2,$^)")) ;\
		f(x) = exp(a)* exp(- b*x) ;\
		g(x) = exp(a - aerr) * exp(- (b + berr)*x) ;\
		h(x) = exp(a + aerr) *exp(- (b - berr)*x) ;\
		plot \
			"$<" using 1:2:3 with errorbars title "data", \
			f(x) with lines lt rgb "black" title sprintf("Fit using Aexp(- b*x), A=%.3f, b = %.3f", exp(a), b), \
			g(x) with lines dashtype 2 lt rgb "black" title "Uncertainty band", \
			h(x) with lines dashtype 2 lt rgb "black" title "" ;\
	' |tee log.activities |gnuplot



main : main.o matrix.o QR-factorization.o vector.o

main.o : main.cc vector.h matrix.h QR-factorization.h OLS.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.cc matrix.h vector.h vector.o

QR-factorization : QR-factorization.o matrix.o vector.o

QR-factorization.o : matrix.h vector.h QR-factorization.h QR-factorization.cc



.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 

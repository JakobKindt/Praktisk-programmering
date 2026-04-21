CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

# all: Out.txt fig_wave_func.svg fig_conv_acc.svg fig_conv_eps.svg fig_conv_rmin.svg fig_conv_rmax.svg

Out.txt : main
	./main > Out.txt 


main : main.o min.o matrix.o vector.o QR-factorization.o

main.o : main.cc min.h vector.h matrix.h QR-factorization.h

vector : vector.o

vector.o : vector.h vector.cc

matrix : matrix.o vector.o

matrix.o : matrix.h matrix.cc vector.h vector.o

min : min.o matrix.o vector.o QR-factorization.o

min.o : min.h min.cc matrix.h vector.h QR-factorization.h

QR-factorization : QR-factorization.o matrix.o vector.o

QR-factorization.o : QR-factorization.cc QR-factorization.h matrix.h vector.h


.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err *.svg *.log log.* *.Identifier *.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
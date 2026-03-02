CXXFLAGS = -Wall -Wextra -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

Out.txt : main
	./main > Out.txt 

main : main.o matrix.o EVD.o

main.o : main.cc vec.h matrix.h EVD.h

matrix : matrix.o

matrix.o : matrix.cc matrix.h vec.h EVD.h

EVD : EVD.o matrix.o

EVD.o : matrix.h vec.h EVD.h EVD.cc


.PHONY:clean 
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o out* err

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 

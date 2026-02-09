CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

# Out.txt : main # This is what the file has to do. The like below runs main and sends it to output. By default, make only makes the first file, otherwise the order does not matter.
# 	./main > Out.txt 

# main : main.o vec.o # The below line will link main.o     CXX is a driver    The lines below are rules. Main is called a dish, main.o and hello.o is called a ingredients and the rules are called a recipy.

# main.o : main.cc vec.h # main.o depends on main.cpp and will compile it, hence the -c and -o means that the output will go to main.o. It is redundant but is included for pædagogiske reasons.
# # 	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

# vec.o: vec.cc vec.h
# # 	$(CXX) $(CXXFLAGS) -c hello.cc -o hello.o

# .PHONY:clean # Purists way, this declares things which are not files as phoneys, which allows us to have another actual file called clean.
# clean: # Forces to remove the stuff listed
# 	$(RM) main main.o Out.txt *.o

Out.txt Err.txt: script.py main data.txt
	python3 $< 2> Err.txt
	./main < data.txt >> Out.txt 2>>Err.txt

data.txt: Makefile
	echo 1 2 >> $@
	echo 2 1 >> $@
	echo 3 3 >> $@
	echo 4 5 >> $@
	echo 5 6 >> $@

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 

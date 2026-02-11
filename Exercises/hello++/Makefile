CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm #L is for link
Out.txt : main # This is what the file has to do. The like below runs main and sends it to output. By default, make only makes the first file, otherwise the order does not matter.
	./main > Out.txt 

# Normally, we do not write rules themselves, only dependencies and write the important stuff in the flags.


# main : main.o # The below line will link main.o
# 	c++ main.o -o main

# main.o : main.cpp # main.o depends on main.cpp and will compile it, hence the -c and -o means that the output will go to main.o. It is redundant but is included for pædagogiske reasons.
# 	c++ -c main.cpp -o main.o

# main : main.o # The below line will link main.o     CXX is a driver
# 	$(CXX) main.o -o main $(LDLIBS)

# main.o : main.cpp # main.o depends on main.cpp and will compile it, hence the -c and -o means that the output will go to main.o. It is redundant but is included for pædagogiske reasons.
# 	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

main : main.o hello.o # The below line will link main.o     CXX is a driver    The lines below are rules. Main is called a dish, main.o and hello.o is called a ingredients and the rules are called a recipy.
	$(CXX) main.o hello.o -o main $(LDLIBS)

main.o : hello.hpp main.cpp # main.o depends on main.cpp and will compile it, hence the -c and -o means that the output will go to main.o. It is redundant but is included for pædagogiske reasons.
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

hello.o: hello.hpp hello.cpp
	$(CXX) $(CXXFLAGS) -c hello.cpp -o hello.o

.PHONEY:clean # Purists way, this declares things which are not files as phoneys, which allows us to have another actual file called clean.
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt
# clean: # Forces to remove the stuff listed
# 	rm --force main main.o Out.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
# 	echo CXX prints "CXX"
#   echo $(CXX) prints the variable CXX. CXX here is the operator system and the language
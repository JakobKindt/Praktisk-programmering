CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) # This does the same a the line below
LDLIBS = -lstdc++ -lm #L is for link

Out.txt : main # This is what the file has to do. The like below runs main and sends it to output. By default, make only makes the first file, otherwise the order does not matter.
	./main > Out.txt 

main : main.o hello.o sfuns.o # The below line will link main.o     CXX is a driver    The lines below are rules. Main is called a dish, main.o and hello.o is called a ingredients and the rules are called a recipy.
#  	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o main
# 	$(CXX) main.o hello.o -o sfuncs main $(LDLIBS)
# $^ this gives all prerequisites, i.e. all the ingredients. This is good for avoiding typos. This used line is already included in main.

main.o : hello.h sfuns.h # main.o depends on main.cpp and will compile it, hence the -c and -o means that the output will go to main.o. It is redundant but is included for pædagogiske reasons.
# 	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

hello.o: hello.h
# 	$(CXX) $(CXXFLAGS) -c hello.cc -o hello.o

sfuns.o: sfuns.h
# 	$(CXX) $(CXXFLAGS) -c sfuns.cc -o sfuns.o

.PHONEY:clean # Purists way, this declares things which are not files as phoneys, which allows us to have another actual file called clean.
clean: # Forces to remove the stuff listed
	$(RM) main main.o Out.txt *.o
# clean: # Forces to remove the stuff listed
# 	rm --force main main.o Out.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM) 
# 	echo CXX prints "CXX"
#   echo $(CXX) prints the variable CXX. CXX here is the operator system and the language


# Out.txt : main # This is what the file has to do. The like below runs main and sends it to output. By default, make only makes the first file, otherwise the order does not matter.
# 	./main > Out.txt 

# main : main.o hello.o sfuns.o # The below line will link main.o     CXX is a driver    The lines below are rules. Main is called a dish, main.o and hello.o is called a ingredients and the rules are called a recipy.
# #  	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o main
# # 	$(CXX) main.o hello.o -o sfuncs main $(LDLIBS)
# # $^ this gives all prerequisites, i.e. all the ingredients. This is good for avoiding typos. This used line is already included in main.

# main.o : hello.h sfuns.h main.cc # main.o depends on main.cpp and will compile it, hence the -c and -o means that the output will go to main.o. It is redundant but is included for pædagogiske reasons.
# # 	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

# hello.o: hello.h hello.cc
# # 	$(CXX) $(CXXFLAGS) -c hello.cc -o hello.o

# sfuns.o: sfuns.h sfuns.cc
# # 	$(CXX) $(CXXFLAGS) -c sfuns.cc -o sfuns.o

# .PHONEY:clean # Purists way, this declares things which are not files as phoneys, which allows us to have another actual file called clean.
# clean: # Forces to remove the stuff listed
# 	$(RM) main main.o Out.txt *.o
# # clean: # Forces to remove the stuff listed
# # 	rm --force main main.o Out.txt

# test:
# 	@echo CXX
# 	@echo $(CXX)
# 	@echo $(RM) 
# # 	echo CXX prints "CXX"
# #   echo $(CXX) prints the variable CXX. CXX here is the operator system and the language
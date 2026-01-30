CXX = c++
CXXFLAGS = -std=c++23
# CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O

Out.txt: numbers
	./numbers > Out.txt

numbers: numbers.o
	$(CXX) numbers.o -o numbers

numbers.o : numbers.cc
	$(CXX) $(CXXFLAGS) -c numbers.cc -o numbers.o

clean:
	$(RM) numbers numbers.o Out.txt

run: numbers
	./numbers $(N)
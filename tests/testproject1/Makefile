CFLAGS=-c -Wall

all: testbin

testbin: main.o secondary.o
	$(CXX) main.o secondary.o -o testbin

main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp

secondary.o: secondary.cpp
	$(CXX) $(CFLAGS) secondary.cpp

clean:
	rm secondary.o main.o testbin
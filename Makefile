GCC=gcc
CFLAGS=-std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
EXEC = sort
TESTFLAGS = -DASCENDING

all: main.c sort.c
	$(GCC) $(CFLAGS) -o $(EXEC) main.c sort.c
	
# Fix the gcc command for the target ascending by fill in the missing part
ascending: main.c sort.c
	$(GCC) $(CFLAGS) $(TESTFLAGS)  -o $(EXEC) main.c sort.c
	
test: all
	./$(EXEC) testcases/inp1
	./$(EXEC) testcases/inp2
	./$(EXEC) testcases/inp3	
	
test-ascending: ascending
	./$(EXEC) testcases/inp1
	./$(EXEC) testcases/inp2
	./$(EXEC) testcases/inp3	
	
clean:
	rm -f $(EXEC)
	rm -f *.o

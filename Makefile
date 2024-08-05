CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DTEST_CREATELIST -DTEST_ELIMINATE -DDEBUG -DTEST_DELETENODE 
GCC = gcc $(CFLAGS) $(TESTFLAGS)
EXEC = main
OBJS = main.o hw10.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) hw10.h
	$(GCC) $(OBJS) -o $(EXEC) 

test: $(EXEC) 
	./$(EXEC) 6 3 > output1
	diff -w output1 testcases/expected1
	./$(EXEC) 4 6 > output2
	diff -w output2 testcases/expected2
	./$(EXEC) 25 7 > output3
	diff -w output3 testcases/expected3

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) 6 3 > output1
	$(VALGRIND) --log-file=log2 ./$(EXEC) 4 6 > output2
	$(VALGRIND) --log-file=log3 ./$(EXEC) 25 7 > output3

	

%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f shuffle.o main.o
	rm -f $(EXEC)
	rm -f id? name? log?
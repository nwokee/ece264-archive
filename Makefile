CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DTEST_BUILDTREE -DTEST_PRINTPATH
GCC = gcc $(CFLAGS) $(TESTFLAGS)
EXEC = main
OBJS =  main.o tree.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) tree.h
	$(GCC) $(OBJS) -o $(EXEC) 


test: $(EXEC) 
	./$(EXEC)  testcases/test1in testcases/test1post > output1
	diff -w output1 expected/expected1
	./$(EXEC)  testcases/test2in testcases/test2post > output2
	diff -w output2 expected/expected2
	./$(EXEC)  testcases/test3in testcases/test3post > output3
	diff -w output3 expected/expected3
	./$(EXEC)  testcases/test4in testcases/test4post > output4
	diff -w output4 expected/expected4
	./$(EXEC)  testcases/test5in testcases/test5post > output5
	diff -w output5 expected/expected5
	./$(EXEC)  testcases/test6in testcases/test6post > output6
	diff -w output6 expected/expected6

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/test1in testcases/test1post > output1
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/test2in testcases/test2post > output2
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/test3in testcases/test3post > output3
	$(VALGRIND) --log-file=log4 ./$(EXEC) testcases/test4in testcases/test4post > output4
	$(VALGRIND) --log-file=log5 ./$(EXEC) testcases/test5in testcases/test5post > output5
	$(VALGRIND) --log-file=log6 ./$(EXEC) testcases/test6in testcases/test6post > output6

%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f shuffle.o main.o
	rm -f $(EXEC)
	rm -f id? name? log?
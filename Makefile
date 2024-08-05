CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DCHECK_PATH
GCC = gcc $(CFLAGS) $(TESTFLAGS)
EXEC = hw9
OBJS =  solver.o hw9.o maze.o mazehelper.o path.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) solver.h maze.h path.h
	$(GCC) $(OBJS) -o $(EXEC) 

test: $(EXEC) 
	./$(EXEC) testcases/maze1  maze1out
	./$(EXEC) testcases/maze2  maze2out
	./$(EXEC) testcases/maze3  maze3out
	./$(EXEC) testcases/maze4  maze4out
	./$(EXEC) testcases/maze5  maze5out

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/maze1  maze1out
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/maze2  maze2out
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/maze3  maze3out
	$(VALGRIND) --log-file=log4 ./$(EXEC) testcases/maze4  maze4out
	$(VALGRIND) --log-file=log5 ./$(EXEC) testcases/maze5  maze5out

%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f shuffle.o main.o
	rm -f $(EXEC)
	rm -f id? name? log?
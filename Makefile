CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DCHECK_PATH
GCC = gcc $(CFLAGS) $(TESTFLAGS)
EXEC = hw11
OBJS =  solver.o hw11.o maze.o mazehelper.o path.o list.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) solver.h maze.h path.h
	$(GCC) $(OBJS) -o $(EXEC) 


test: $(EXEC) 
	./$(EXEC)  testcases/maze1 maze1out
	diff -w maze1out expected/expected1
	./$(EXEC)  testcases/maze2 maze2out
	diff -w maze2out expected/expected2
	./$(EXEC)  testcases/maze3 maze3out
	diff -w maze3out expected/expected3


memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/maze1  maze1out
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/maze2  maze2out
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/maze3  maze3out

%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f shuffle.o main.o
	rm -f $(EXEC)
	rm -f id? name? log?
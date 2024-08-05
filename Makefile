CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DTEST_READ -DTEST_WRITE -DTEST_DIVIDE -DTEST_INTERLEAVE -DTEST_SHUFFLE -fPIE
GCC = gcc $(CFLAGS) $(TESTFLAGS)
EXEC = main
OBJS =  shuffle.o main.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) shuffle.h
	$(GCC) $(OBJS) -o $(EXEC) 

test: $(EXEC) 
	./$(EXEC) 4 | sort > output4
	diff -w output4 expected/expected4
	./$(EXEC) 8 | sort > output8
	diff -w output8 expected/expected8
	./$(EXEC) 11 | sort > output11
	diff -w output11 expected/expected11

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) 4 | sort > output4
	$(VALGRIND) --log-file=log2 ./$(EXEC) 8 | sort > output8
	$(VALGRIND) --log-file=log3 ./$(EXEC) 11 | sort > output11

%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f shuffle.o main.o
	rm -f $(EXEC)
	rm -f id? name? log?

# You MUST modify this file

GCC=gcc $(CFLAGS) $(RUN_INTEGRATE) $(TEST_INTEGRATE)
CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
LIBS = -lm
EXEC = hw4
FUNCS = func1.c func2.c func3.c func4.c func5.c
SRCS =  hw4.c integrator-hw4.c $(FUNCS)
RUN_INTEGRATE = -DRUN_INTEGRATE
TEST_INTEGRATE = -DTEST_INTEGRATE

all : hw4.c integrator-hw4.c
	$(GCC) $(CFLAGS) $(RUN_INTEGRATE) $(TEST_INTEGRATE) $(FUNCS) -c -lm $<



%.o : %.c
	$(GCC) $(CFLAGS) - $<

$(EXEC): $(SRCS) hw4.h
	$(GCC) $(SRCS) -o $(EXEC) $(LIBS) 
testall : $(EXEC)
	./$(EXEC) testcases/test1 testcases/output1
	./$(EXEC) testcases/test2 testcases/output2
	./$(EXEC) testcases/test3 testcases/output3
	./$(EXEC) testcases/test4 testcases/output4
clean:
	rm -f *.o
	rm -f testgen 
	rm -f *.gcda *.gcno gmon.out *gcov
	rm -f hw4 hw4.prof

CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
LIBS = -lm
EXEC = hw14
SRCS = hw14.c huffman.c
GCC = gcc $(CFLAGS)
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose --leak-check=full

$(EXEC): $(SRCS)
	$(GCC) $(SRCS) -o $(EXEC) 
test: $(EXEC)
	./$(EXEC) testcases/basic basic_sorted basic_huffman basic_header
	diff -w basic_sorted expected/basic_sorted
	diff -w basic_huffman expected/basic_huffman
	diff -w basic_header expected/basic_header
	./$(EXEC) testcases/gophers gophers_sorted gophers_huffman gophers_header
	diff -w gophers_sorted expected/gophers_sorted
	diff -w gophers_huffman expected/gophers_huffman
	diff -w gophers_header expected/gophers_header
	./$(EXEC) testcases/para para_sorted para_huffman para_header
	diff -w para_sorted expected/para_sorted
	diff -w para_huffman expected/para_huffman
	diff -w para_header expected/para_header
	./$(EXEC) testcases/prideandprejudice prideandprejudice_sorted prideandprejudice_huffman prideandprejudice_header
	diff -w prideandprejudice_sorted expected/prideandprejudice_sorted
	diff -w prideandprejudice_huffman expected/prideandprejudice_huffman
	diff -w prideandprejudice_header expected/prideandprejudice_header
	./$(EXEC) testcases/woods woods_sorted woods_huffman woods_header
	diff -w woods_sorted expected/woods_sorted
	diff -w woods_huffman expected/woods_huffman
	diff -w woods_header expected/woods_header

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/basic basic_sorted basic_huffman basic_header
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/gophers gophers_sorted gophers_huffman gophers_header
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/para para_sorted para_huffman para_header
	$(VALGRIND) --log-file=log4 ./$(EXEC) testcases/prideandprejudice prideandprejudice_sorted prideandprejudice_huffman prideandprejudice_header
	$(VALGRIND) --log-file=log5 ./$(EXEC) testcases/woods woods_sorted woods_huffman woods_header

clean:
	rm -f basic* gophers* para* prideandprejudice* woods* log* *.o
	rm -f hw14
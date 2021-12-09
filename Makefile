test : test.c
	clang -o test test.c && ./test
.PHONY : test
main : test.c
	clang -o main test.c

test : test.c
	clang -o test test.c && ./test
	rm -f ./test
.PHONY : test main
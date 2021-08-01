all: zmalloc-test

zmalloc-test: zmalloc.c zmalloc.h testhelp.h
	$(CC) -o zmalloc-test zmalloc.c -Wall -std=c99 -pedantic -O2 -DZMALLOC_TEST_MAIN
	@echo ">>> Type ./zmalloc-test to run the zmalloc.c unit tests."

clean:
	rm -f zmalloc-test

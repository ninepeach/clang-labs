all: dict-test

dict-test: main.c dict.c
	$(CC) -o dict-test main.c sds.c dict.c zmalloc.c -Wall -std=c99 -pedantic -O2 -DDICT_TEST_MAIN
	@echo ">>> Type ./dict-test to run the dict.c unit tests."

clean:
	rm -f dict-test

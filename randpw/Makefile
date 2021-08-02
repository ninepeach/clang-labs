all: randpw-test

randpw-test: randpw.c randpw.h
	$(CC) -o randpw-test randpw.c -Wall -std=c99 -pedantic -O2 -DRANDPW_TEST_MAIN
	@echo ">>> Type ./randpw-test to run the randpw.c test."

clean:
	rm -f randpw-test

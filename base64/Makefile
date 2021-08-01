all: base64-test

base64-test: base64.c base64.h
	$(CC) -o base64-test base64.c -Wall -std=c99 -pedantic -O2 -DBASE64_TEST_MAIN
	@echo ">>> Type ./base64-test to run the base64.c test."

clean:
	rm -f base64-test

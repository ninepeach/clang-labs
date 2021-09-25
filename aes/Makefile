all: aes-test

aes-test: test.c aes.c aes.h
	$(CC) -o aes-test test.c aes.c -Wall -std=c99 -pedantic -O2
	@echo ">>> Type ./aes-test to run the aes.c test."

clean:
	rm -f aes-test

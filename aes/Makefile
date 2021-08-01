all: aes-test

aes-test: aes.c aes.h
	$(CC) -o aes-test aes.c -Wall -std=c99 -pedantic -O2 -DAES_TEST_MAIN
	@echo ">>> Type ./aes-test to run the aes.c test."

clean:
	rm -f aes-test

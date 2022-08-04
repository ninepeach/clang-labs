all: cidr-test

cidr-test: main.c cidr.c cidr.h
	$(CC) -o cidr-test main.c cidr.c -Wall -std=c99 -pedantic -O2 -DCIDR_TEST_MAIN
	@echo ">>> Type ./cidr-test to run the cidr.c test."
clean:
	rm -f cidr-test


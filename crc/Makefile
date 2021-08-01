all: crc64-test crc16-test

crc64-test: crc64.c crc64.h
	$(CC) -o crc64-test crc64.c -Wall -std=c99 -pedantic -O2 -DCRC64_TEST_MAIN
	@echo ">>> Type ./crc64-test to run the crc64.c test."

crc16-test: crc16.c crc16.h
	$(CC) -o crc16-test crc16.c -Wall -std=c99 -pedantic -O2 -DCRC16_TEST_MAIN
	@echo ">>> Type ./crc16-test to run the crc16.c test."

clean:
	rm -f crc64-test
	rm -f crc16-test


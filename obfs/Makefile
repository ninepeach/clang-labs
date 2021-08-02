all: obfs-test

obfs-test: obfs.c obfs_http.c obfs.h obfs_http.h
	$(CC) -o obfs-test obfs.c obfs_http.c ../sds/sds.c ../base64/base64.c -Wall -std=c99 -pedantic -O2 -DOBFS_TEST_MAIN
	@echo ">>> Type ./obfs-test to run the obfs.c test."

clean:
	rm -f obfs-test

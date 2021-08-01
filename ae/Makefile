all: example-timer example-client example-server 

example-timer: examples/example-timer.c
	$(CC) -o examples/example-timer examples/example-timer.c ae.c anet.c -Wall -std=c99 -pedantic -O2
	@echo ">>> Type ./examples/example-timer to run the example-timer."

example-client: examples/example-client.c
	$(CC) -o examples/example-client examples/example-client.c ae.c anet.c -Wall -std=c99 -pedantic -O2
	@echo ">>> Type ./examples/example-client to run the example-client."

example-server: examples/example-server.c
	$(CC) -o examples/example-server examples/example-server.c ae.c anet.c -Wall -std=c99 -pedantic -O2
	@echo ">>> Type ./examples/example-server to run the example-server."

clean:
	rm -f examples/example-timer
	rm -f examples/example-client
	rm -f examples/example-server

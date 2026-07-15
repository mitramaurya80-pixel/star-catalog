CC  =gcc
CFLAGS=-Wall

queuetree.o: queuetree.c helper.h
	$(CC) $(CFLAGS) -c queuetree.c
helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c

main: queuetree.o helper.o
	$(CC) $(CFLAGS) queuetree.o helper.o -o queue


run: main
	./queue

clean:
	rm -rf *.o queue
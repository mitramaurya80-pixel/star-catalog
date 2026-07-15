CC  =gcc
CFLAGS=-Wall

star-catalog.o: src/star-catalog.c src/helper.h
	$(CC) $(CFLAGS) -c src/star-catalog.c
helper.o: src/helper.c src/helper.h
	$(CC) $(CFLAGS) -c src/helper.c

main: star-catalog.o helper.o
	$(CC) $(CFLAGS) star-catalog.o helper.o -o star-catalog


run: main
	./star-catalog

clean:
	rm -rf *.o star-catalog
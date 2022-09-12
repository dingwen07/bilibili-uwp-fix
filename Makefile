CC = gcc
CFLAGS = -Wall


all: biliuwpfix

biliuwpfix: biliuwpfix.c
	$(CC) $(CFLAGS) -o biliuwpfix biliuwpfix.c

clean:
	rm -f biliuwpfix

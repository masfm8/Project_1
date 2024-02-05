CC = gcc
CFLAGS = -Wall -std=c99

all: oss user

oss: oss.c
	$(CC) $(CFLAGS) oss.c -o oss

user: user.c
	$(CC) $(CFLAGS) user.c -o user

clean:
	rm -f oss user

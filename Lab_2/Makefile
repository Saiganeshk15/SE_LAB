# Variables for the compiler and flags
CC = gcc
CFLAGS = -Wall -g

TARGET = student_app
OBJS = main.o utils.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJS) $(TARGET)
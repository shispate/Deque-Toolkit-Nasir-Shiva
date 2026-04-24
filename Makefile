# Author:        Shiva Patel & Nasir Davis
# File:          Makefile
# Last Modified: 2024-04-14
# Purpose:       Build the deque project

CC     = g++
TARGET = deque_toolkit
CFLAGS = -Wall -Wextra
OBJS   = main.o deque.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.cpp deque.h
	$(CC) $(CFLAGS) -c main.cpp

deque.o: deque.cpp deque.h
	$(CC) $(CFLAGS) -c deque.cpp

clean:
	rm -f $(OBJS) $(TARGET)
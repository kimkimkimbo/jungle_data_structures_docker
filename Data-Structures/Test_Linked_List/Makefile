# Makefile for Linked List test

CC = gcc
CFLAGS = -g -I../Linked_List   # -I로 헤더 파일 경로 추가
TARGET = test_insertSortedLL
SRCS = test_insertSortedLL.c ../Linked_List/Q1_A_LL.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

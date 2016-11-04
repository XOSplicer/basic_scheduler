BUILD_DIR := build
SRC_DIR		:= src
H_DIR			:= h


all: main tests.o

main: main.o tests.o scheduler.o queue.o
	gcc -o $(BUILD_DIR)/main $(BUILD_DIR)/main.o $(BUILD_DIR)/tests.o $(BUILD_DIR)/scheduler.o $(BUILD_DIR)/queue.o

main.o: $(SRC_DIR)/main.c
	gcc -o $(BUILD_DIR)/main.o -c $(SRC_DIR)/main.c

tests.o: $(SRC_DIR)/tests.c
	gcc -o $(BUILD_DIR)/tests.o -c $(SRC_DIR)/tests.c

scheduler.o: $(SRC_DIR)/scheduler.c $(H_DIR)/scheduler.h
	gcc -o $(BUILD_DIR)/scheduler.o -c $(SRC_DIR)/scheduler.c

queue.o: $(SRC_DIR)/queue.c $(H_DIR)/queue.h
	gcc -o $(BUILD_DIR)/queue.o -c $(SRC_DIR)/queue.c

clean:
	rm build/*

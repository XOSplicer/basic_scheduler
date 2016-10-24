
all: sched

sched: main.o scheduler.o
	gcc -o sched main.o scheduler.o

main.o: main.c
	gcc -c main.c

scheduler.o: scheduler.c scheduler.h
	gcc -c scheduler.c

clean:
	rm sched
	rm main.o
	rm scheduler.o

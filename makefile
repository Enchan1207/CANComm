includePath = -I SocketCAN/ -I ReceiveThread/ -I Queue/

a.out: func.o Receive.o SocketCAN.o Queue
	gcc $(includePath) Queue.o Dump.o Item.o SocketCAN.o Receive.o func.o main.c -o a.out -pthread

func.o: func.c
	gcc $(includePath) -c func.c

Receive.o: ReceiveThread/Receive.c
	gcc $(includePath) -c ReceiveThread/Receive.c -pthread

SocketCAN.o: SocketCAN/SocketCAN.c
	gcc $(includePath) -c SocketCAN/SocketCAN.c

Queue: Queue/Queue.c Queue/Dump.c Queue/Item.c Queue/Queue.h
	gcc $(includePath) -c Queue/Queue.c -std=c11 -pthread
	gcc $(includePath) -c Queue/Dump.c -std=c11
	gcc $(includePath) -c Queue/Item.c -std=c11
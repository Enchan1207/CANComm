includePath = -I SocketCAN/ -I ReceiveThread/ -I Queue/ -I FrameAnalyse
debug = #-g -O0
options = $(debug) $(includePath)

a.out: func.o Receive.o SocketCAN.o Analyse.o libQueue
	gcc $(options) Queue.o Dump.o Item.o SocketCAN.o Receive.o Analyse.o func.o main.c -o a.out -pthread

func.o: func.c
	gcc $(options) -c func.c

Receive.o: ReceiveThread/Receive.c
	gcc $(options) -c ReceiveThread/Receive.c -pthread

Analyse.o: FrameAnalyse/Analyse.c
	gcc $(options) -c FrameAnalyse/Analyse.c -pthread

SocketCAN.o: SocketCAN/SocketCAN.c
	gcc $(options) -c SocketCAN/SocketCAN.c

.PHONY: libQueue
libQueue: Queue/Queue.c Queue/Dump.c Queue/Item.c Queue/Queue.h
	gcc $(options) -c Queue/Queue.c -std=c11 -pthread
	gcc $(options) -c Queue/Dump.c -std=c11
	gcc $(options) -c Queue/Item.c -std=c11
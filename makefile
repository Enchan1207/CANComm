includePath = -I SocketCAN/ -I ReceiveThread/

a.out: func.o Receive.o SocketCAN.o
	gcc $(includePath) SocketCAN.o Receive.o func.o main.c -o a.out -pthread

func.o: func.c
	gcc $(includePath) -c func.c

Receive.o: ReceiveThread/Receive.c
	gcc $(includePath) -c ReceiveThread/Receive.c -pthread

SocketCAN.o: SocketCAN/SocketCAN.c
	gcc $(includePath) -c SocketCAN/SocketCAN.c

# a.out: SocketCAN.so func.c func.h Receive_Thread
# 	gcc -c func.c
# 	gcc $(includePath) SocketCAN.so Receive.o func.o main.c -o a.out -pthread

# .PHONY: Receive_Thread
# Receive_Thread: ReceiveThread/Receive.c
# 	gcc $(includePath) -c ReceiveThread/Receive.c -pthread

# SocketCAN.so: SocketCAN/SocketCAN.h SocketCAN/SocketCAN.c
# 	gcc $(includePath) -shared -fPIC -o SocketCAN.so SocketCAN/SocketCAN.c

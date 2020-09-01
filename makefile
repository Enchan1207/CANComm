Build: main.c lib/SocketCAN/SocketCAN.c lib/func.c lib/ReceiveThread/Receive.c
	gcc -c -I ./ lib/SocketCAN/SocketCAN.c
	gcc -c -I ./ lib/ReceiveThread/Receive.c
	gcc -c -I ./ lib/func.c
	gcc -I ./ main.c SocketCAN.o func.o Receive.o -pthread

Debug: main.c lib/SocketCAN/SocketCAN.c lib/func.c lib/ReceiveThread/Receive.c
	gcc -g -O0 -c -I ./ lib/SocketCAN/SocketCAN.c
	gcc -g -O0 -c -I ./ lib/ReceiveThread/Receive.c
	gcc -g -O0 -c -I ./ lib/func.c
	gcc -g -O0 -I ./ main.c SocketCAN.o func.o Receive.o -pthread
includePath = -I SocketCAN/ -I ReceiveThread/
stdVer = -std=c11
options = $(stdVer) $(includePath)

a.out: SocketCAN.dll func.c func.h Receive_Thread
	gcc $(options) SocketCAN.dll ReceiveThread.o -o a.out

.PHONY: Receive_Thread
Receive_Thread: ReceiveThread/ReceiveThread.c11
	gcc $(options) -c ReceiveThread/ReceiveThread.c

SocketCAN.dll: SocketCAN/SocketCAN.h SocketCAN/SocketCAN.c
	gcc $(options) -c SocketCAN/SocketCAN.c
	gcc $(options) SocketCAN.o -o SocketCAN.dll -shared -pthread

# Build: main.c lib/SocketCAN/SocketCAN.c lib/func.c lib/ReceiveThread/Receive.c
# 	gcc -c -I ./ lib/SocketCAN/SocketCAN.c
# 	gcc -c -I ./ lib/ReceiveThread/Receive.c
# 	gcc -c -I ./ lib/func.c
# 	gcc -I ./ main.c SocketCAN.o func.o Receive.o -pthread

# Debug: main.c lib/SocketCAN/SocketCAN.c lib/func.c lib/ReceiveThread/Receive.c
# 	gcc -g -O0 -c -I ./ lib/SocketCAN/SocketCAN.c
# 	gcc -g -O0 -c -I ./ lib/ReceiveThread/Receive.c
# 	gcc -g -O0 -c -I ./ lib/func.c
# 	gcc -g -O0 -I ./ main.c SocketCAN.o func.o Receive.o -pthread
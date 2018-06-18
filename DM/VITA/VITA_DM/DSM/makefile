curr_dir = $(shell pwd)
out_dir = $(curr_dir)/../Executables/lib/
wifidir = $(shell pwd)/Linux/WIFI
btdir = $(shell pwd)/Linux/BT
bledir = $(shell pwd)/Linux/BLE
INCLUDES = $(curr_dir)../

.PHONY = all
all: libDSM.so

libDSM.so: DM_DSM.o
	$(CC) $(CFLAGS) -shared -o $(out_dir)libDSM.so DM_DSM.o

DM_DSM.o: Source/DM_DSM.c
	$(CC) -c $(CFLAGS) -fPIC Source/DM_DSM.c -o DM_DSM.o

#LINUX
#Android

#iOS

.PHONY = clean
clean:
	rm -f *.o

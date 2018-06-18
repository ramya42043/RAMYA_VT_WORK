curr_dir = $(shell pwd)
out_dir = $(curr_dir)/../../Executables/lib/
wifidir = $(shell pwd)/../Linux/WIFI
btdir = $(shell pwd)/../Linux/BT
bledir = $(shell pwd)/../Linux/BLE
INCLUDES = $(curr_dir)/../../

.PHONY = all
all: libDeM.so

libDeM.so: DM_DeM.o
	$(CC) $(CFLAGS) -shared -o $(out_dir)libDeM.so DM_DeM.o

DM_DeM.o: DM_DeM.c
	$(CC) -c $(CFLAGS) -fPIC DM_DeM.c -o DM_DeM.o -L$(out_dir)

#LINUX
#Android

#iOS

.PHONY = clean
clean:
	$(MAKE) -C $(btdir) clean
	$(MAKE) -C $(wifidir) clean
	$(MAKE) -C $(bledir) clean
	rm -f *.o

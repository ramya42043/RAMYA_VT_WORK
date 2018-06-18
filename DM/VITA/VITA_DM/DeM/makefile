curr_dir = $(shell pwd)
out_dir = $(curr_dir)/../Executables/lib/
INCLUDES = $(curr_dir)../

.PHONY = all
all: libDeM.so

libDeM.so: DM_DeM.o
	$(CC) -shared -o $(out_dir)libDeM.so DM_DeM.o

DM_DeM.o: Source/DM_DeM.c
	$(CC) -c $(CFLAGS) -fPIC Source/DM_DeM.c -o DM_DeM.o

#LINUX
#Android

#iOS

.PHONY = clean
clean:
	rm -f *.o

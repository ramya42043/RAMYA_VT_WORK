curr_dir = $(shell pwd)
out_dir = $(curr_dir)/../Executables/lib/
INCLUDES = $(curr_dir)../

.PHONY = all
all: libCM.so

libCM.so: DM_CM.o
	$(CC) $(CFLAGS) -shared -o $(out_dir)libCM.so DM_CM.o

DM_CM.o: Source/DM_CM.c
	$(CC) -c $(CFLAGS) -fPIC Source/DM_CM.c -o DM_CM.o

.PHONY = clean
clean:
	rm -f *.o

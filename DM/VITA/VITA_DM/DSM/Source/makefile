
curr_dir = $(shell pwd)
out_dir = $(curr_dir)/../../Executables/lib/
INCLUDES = $(curr_dir)/../../

libDSM.so: DM_DSM.c.o 
	$(CC) -shared -o $(out_dir)libDSM.so DM_DSM.c.o -lcurl -ljson-c 


VITA_DM_IoTvity_DSM.o: VITA_DM_IoTvity_DSM.c
	$(CC) -c $(CFLAGS) -fPIC -I$(INCLUDES)Utilities -I$(INCLUDES)Headers/ -I$(INCLUDES)DSM/Headers/ DM_DSM.c.c -o DM_DSM.c.o

	
.PHONY = clean
clean:
	rm -f *.o

#/*
#*	Makefile for the Data Manager project				*
#*	Target builds as library and an test application	*
#*/
CC = gcc
curr_dir = $(shell pwd)/
out_dir = $(curr_dir)../Executables/lib/
DeMdir = $(curr_dir)../DeM/
DsMdir = $(curr_dir)../DSM/
CMdir = $(curr_dir)../CM/
maindir = $(curr_dir)../Test/
INCLUDES = $(curr_dir)

.PHONY = all

VPATH = ../Utilities:json

all: libDM.so libDeM.so libDSM.so libCM.so main

libDM.so: json_helper.o VITA_DM.o 
	$(CC) -shared -o $(out_dir)libDM.so VITA_DM.o $(curr_dir)json/json_helper.o -ljson-c -lpthread

json_helper.o: json/json_helper.c
	@echo "============="
	@echo "VITA_DM/Source/json"
	@echo "============="
	$(CC) -c $(CFLAGS) -fPIC -I$(INCLUDES)../Headers -I$(INCLUDES)../Utilities $(curr_dir)json/json_helper.c -o $(curr_dir)json/json_helper.o

VITA_DM.o: VITA_DM.c
	@echo "============="
	@echo "VITA_DM/Source"
	@echo "============="
	$(CC) -c $(CFLAGS) -fPIC -I$(INCLUDES)../Headers VITA_DM.c -o VITA_DM.o	

libDeM.so:
	@echo "============="
	@echo "VITA_DM/Source - Calling DeM Makefile"
	@echo "============="
	$(MAKE) -C $(DeMdir) CC=$(CC) CFLAGS=$(CFLAGS)
	
libDSM.so:
	@echo "============="
	@echo "VITA_DM/Source - Calling DSM Makefile"
	@echo "============="
	$(MAKE) -C $(DsMdir) CC=$(CC) CFLAGS=$(CFLAGS)
	
libCM.so:
	@echo "============="
	@echo "VITA_DM/Source - Calling CM Makefile"
	@echo "============="
	$(MAKE) -C $(CMdir) CC=$(CC) CFLAGS=$(CFLAGS)
main:
	@echo "============="
	@echo "VITA_DM/Source - Calling UNIT TEST main"
	@echo "============="
	$(MAKE) -C $(maindir) CC=$(CC) CFLAGS=$(CFLAGS)

.PHONY = clean
clean:
	$(MAKE) -C $(DeMdir) clean
	$(MAKE) -C $(DsMdir) clean
	$(MAKE) -C $(CMdir) clean
	rm -f *.o

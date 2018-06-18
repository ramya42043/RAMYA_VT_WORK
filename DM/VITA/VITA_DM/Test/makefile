# the compiler: gcc for C program
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g

curr_dir = $(shell pwd)

all : main

main :
	gcc testapp.c -o testapp -ljson -L$(curr_dir)/../Executables/lib/ -lDM -lDeM -lCM -lDSM -L$(curr_dir)/../DM_IoTvity/ -lDM_iotivity -L$(curr_dir)/../DM_IoTvity/iotivity-1.2.1/out/linux/x86_64/release -lcoap -lconnectivity_abstraction -loc_logger -loctbstack -loc

clean :
	rm *.exe

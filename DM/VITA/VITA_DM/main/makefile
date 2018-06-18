curr_dir = $(shell pwd)

all : main

main :
	gcc main.c -o main.exe -L$(curr_dir)/../Executables/lib -lDM -lDeM -lCM -lDSM -L$(curr_dir)/../DM_IoTvity -lDM_iotivity -ljson -L$(curr_dir)/../DM_IoTvity/iotivity-1.2.1/out/linux/x86_64/release -lcoap -lconnectivity_abstraction -loc_logger -loctbstack -loc

clean :
	rm *.exe

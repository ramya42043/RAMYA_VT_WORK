rm -rf /VITA_TL/RPI_MQTT/raspberry-pi-mqtt-master/program
rm -rf /VITA_TL/RPI_MQTT/raspberry-pi-mqtt-master/sample
#find . -type f -name '*.so' -delete
#find . -type f -name '*.o' -delete
rm VITA_DM/Source/json/json_helper.o
cd VITA_DM/Source/
make clean
make
cd ../../
cd VITA_TL/RPI_MQTT/raspberry-pi-mqtt-master/
make


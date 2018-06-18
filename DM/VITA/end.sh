#!/bin/bash

cd VITA_DM/DM_IoTvity/iotivity-1.2.1/
#git clone https://github.com/01org/tinycbor.git extlibs/tinycbor/tinycbor -b v0.4
scons -c
cd ../..
scons -c
cd Source/
make clean
#./m.bat
#rm -rf VITA_DM/DM_IoTvity/iotivity-1.2.1/extlibs/tinycbor/tinycbor/
#rm -rf VITA_DM/DM_IoTvity/iotivity-1.2.1/extlibs/gtest/gtest-1.7.0
#rm -rf VITA_DM/DM_IoTvity/iotivity-1.2.1/extlibs/gtest/gtest-1.7.0.zip 
#./r.bat



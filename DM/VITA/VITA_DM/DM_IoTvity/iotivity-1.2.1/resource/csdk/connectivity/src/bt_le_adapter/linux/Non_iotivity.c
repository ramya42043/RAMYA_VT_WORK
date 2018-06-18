/**********************************************************************************************
* VOTARYTECH SOFTTECH SOLUTIONS PVT. LTD. CONFIDENTIAL [2009]-[2016]
*  All Rights Reserved. *
* NOTICE: This file is part of {project}.
* All information contained herein is, and remains the property of Votary Softech Solutions Pvt. Ltd.
* and its suppliers,if any.
* Dissemination of this information or reproduction of this material  is strictly forbidden unless prior written permission is obtained
* from Votary Softech Solutions Pvt. Ltd.
.
Author:                                                Date:
Description:

Revision History
----------------------
Bug ID:                                             Author:                                                                Date:
ChangeID:                                           Author:                                                                Date:
************************************************************************************************/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>
#include<semaphore.h>
#include<pthread.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/l2cap.h>
#include "Non_iotivity.h"

void *client_observe(void);
key_value_pair_t1* get(uint8_t* URI);

typedef struct
{
    unsigned char mac_id[50];
    key_value_pair_t1 *observe_pair;
}OBSERVE_T;

static OBSERVE_T   obs_table[MAX_SIZE];
static int obs_table_index = 0;
key_value_pair_t1 *NI_testGetdata = NULL;
info NI_characteristic_table[MAX_SIZE];
BLE_Device_InfoTable_t NonIotivity_BLE_Device_InfoTable;
static int32_t NI_table_index = 0;
pthread_mutex_t mutex_lock_noniot;
extern void terminateListofIOTDevices(void);
/////////////////
uuid_table_t uuid_table[] = {
    {0x0001, "SDP"},
    {0x0003, "RFCOMM"},
    {0x0005, "TCS-BIN"},
    {0x0007, "ATT"},
    {0x0008, "OBEX"},
    {0x000f, "BNEP"},
    {0x0010, "UPNP"},
    {0x0011, "HIDP"},
    {0x0012, "Hardcopy Control Channel"},
    {0x0014, "Hardcopy Data Channel"},
    {0x0016, "Hardcopy Notification"},
    {0x0017, "AVCTP"},
    {0x0019, "AVDTP"},
    {0x001b, "CMTP"},
    {0x001e, "MCAP Control Channel"},
    {0x001f, "MCAP Data Channel"},
    {0x0100, "L2CAP"},
    /* 0x0101 to 0x0fff undefined */
    {0x1000, "Service Discovery Server Service Class"},
    {0x1001, "Browse Group Descriptor Service Class"},
    {0x1002, "Public Browse Root"},
    /* 0x1003 to 0x1100 undefined */
    {0x1101, "Serial Port"},
    {0x1102, "LAN Access Using PPP"},
    {0x1103, "Dialup Networking"},
    {0x1104, "IrMC Sync"},
    {0x1105, "OBEX Object Push"},
    {0x1106, "OBEX File Transfer"},
    {0x1107, "IrMC Sync Command"},
    {0x1108, "Headset"},
    {0x1109, "Cordless Telephony"},
    {0x110a, "Audio Source"},
    {0x110b, "Audio Sink"},
    {0x110c, "A/V Remote Control Target"},
    {0x110d, "Advanced Audio Distribution"},
    {0x110e, "A/V Remote Control"},
    {0x110f, "A/V Remote Control Controller"},
    {0x1110, "Intercom"},
    {0x1111, "Fax"},
    {0x1112, "Headset AG"},
    {0x1113, "WAP"},
    {0x1114, "WAP Client"},
    {0x1115, "PANU"},
    {0x1116, "NAP"},
    {0x1117, "GN"},
    {0x1118, "Direct Printing"},
    {0x1119, "Reference Printing"},
    {0x111a, "Basic Imaging Profile"},
    {0x111b, "Imaging Responder"},
    {0x111c, "Imaging Automatic Archive"},
    {0x111d, "Imaging Referenced Objects"},
    {0x111e, "Handsfree"},
    {0x111f, "Handsfree Audio Gateway"},
    {0x1120, "Direct Printing Refrence Objects Service"},
    {0x1121, "Reflected UI"},
    {0x1122, "Basic Printing"},
    {0x1123, "Printing Status"},
    {0x1124, "Human Interface Device Service"},
    {0x1125, "Hardcopy Cable Replacement"},
    {0x1126, "HCR Print"},
    {0x1127, "HCR Scan"},
    {0x1128, "Common ISDN Access"},
    /* 0x1129 and 0x112a undefined */
    {0x112d, "SIM Access"},
    {0x112e, "Phonebook Access Client"},
    {0x112f, "Phonebook Access Server"},
    {0x1130, "Phonebook Access"},
    {0x1131, "Headset HS"},
    {0x1132, "Message Access Server"},
    {0x1133, "Message Notification Server"},
    {0x1134, "Message Access Profile"},
    {0x1135, "GNSS"},
    {0x1136, "GNSS Server"},
    {0x1137, "3D Display"},
    {0x1138, "3D Glasses"},
    {0x1139, "3D Synchronization"},
    {0x113a, "MPS Profile"},
    {0x113b, "MPS Service"},
    /* 0x113c to 0x11ff undefined */
    {0x1200, "PnP Information"},
    {0x1201, "Generic Networking"},
    {0x1202, "Generic File Transfer"},
    {0x1203, "Generic Audio"},
    {0x1204, "Generic Telephony"},
    {0x1205, "UPNP Service"},
    {0x1206, "UPNP IP Service"},
    {0x1300, "UPNP IP PAN"},
    {0x1301, "UPNP IP LAP"},
    {0x1302, "UPNP IP L2CAP"},
    {0x1303, "Video Source"},
    {0x1304, "Video Sink"},
    {0x1305, "Video Distribution"},
    /* 0x1306 to 0x13ff undefined */
    {0x1400, "HDP"},
    {0x1401, "HDP Source"},
    {0x1402, "HDP Sink"},
    /* 0x1403 to 0x17ff undefined */
    {0x1800, "Generic Access Profile"},
    {0x1801, "Generic Attribute Profile"},
    {0x1802, "Immediate Alert"},
    {0x1803, "Link Loss"},
    {0x1804, "Tx Power"},
    {0x1805, "Current Time Service"},
    {0x1806, "Reference Time Update Service"},
    {0x1807, "Next DST Change Service"},
    {0x1808, "Glucose"},
    {0x1809, "Health Thermometer"},
    {0x180a, "Device Information"},
    /* 0x180b and 0x180c undefined */
    {0x180d, "Heart Rate"},
    {0x180e, "Phone Alert Status Service"},
    {0x180f, "Battery Service"},
    {0x1810, "Blood Pressure"},
    {0x1811, "Alert Notification Service"},
    {0x1812, "Human Interface Device"},
    {0x1813, "Scan Parameters"},
    {0x1814, "Running Speed and Cadence"},
    {0x1815, "Automation IO"},
    {0x1816, "Cycling Speed and Cadence"},
    /* 0x1817 undefined */
    {0x1818, "Cycling Power"},
    {0x1819, "Location and Navigation"},
    {0x181a, "Environmental Sensing"},
    {0x181b, "Body Composition"},
    {0x181c, "User Data"},
    {0x181d, "Weight Scale"},
    {0x181e, "Bond Management"},
    {0x181f, "Continuous Glucose Monitoring"},
    {0x1820, "Internet Protocol Support"},
    {0x1821, "Indoor Positioning"},
    {0x1822, "Pulse Oximeter"},
    {0x1823, "HTTP Proxy"},
    {0x1824, "Transport Discovery"},
    {0x1825, "Object Transfer"},
    /* 0x1824 to 0x27ff undefined */
    {0x2800, "Primary Service"},
    {0x2801, "Secondary Service"},
    {0x2802, "Include"},
    {0x2803, "Characteristic"},
    /* 0x2804 to 0x28ff undefined */
    {0x2900, "Characteristic Extended Properties"},
    {0x2901, "Characteristic User Description"},
    {0x2902, "Client Characteristic Configuration"},
    {0x2903, "Server Characteristic Configuration"},
    {0x2904, "Characteristic Format"},
    {0x2905, "Characteristic Aggregate Formate"},
    {0x2906, "Valid Range"},
    {0x2907, "External Report Reference"},
    {0x2908, "Report Reference"},
    {0x2909, "Number of Digitals"},
    {0x290a, "Value Trigger Setting"},
    {0x290b, "Environmental Sensing Configuration"},
    {0x290c, "Environmental Sensing Measurement"},
    {0x290d, "Environmental Sensing Trigger Setting"},
    {0x290e, "Time Trigger Setting"},
    /* 0x290f to 0x29ff undefined */
    {0x2a00, "Device Name"},
    {0x2a01, "Appearance"},
    {0x2a02, "Peripheral Privacy Flag"},
    {0x2a03, "Reconnection Address"},
    {0x2a04, "Peripheral Preferred Connection Parameters"},
    {0x2a05, "Service Changed"},
    {0x2a06, "Alert Level"},
    {0x2a07, "Tx Power Level"},
    {0x2a08, "Date Time"},
    {0x2a09, "Day of Week"},
    {0x2a0a, "Day Date Time"},
    /* 0x2a0b undefined */
    {0x2a0c, "Exact Time 256"},
    {0x2a0d, "DST Offset"},
    {0x2a0e, "Time Zone"},
    {0x2a0f, "Local Time Information"},
    /* 0x2a10 undefined */
    {0x2a11, "Time with DST"},
    {0x2a12, "Time Accuracy"},
    {0x2a13, "Time Source"},
    {0x2a14, "Reference Time Information"},
    /* 0x2a15 undefined */
    {0x2a16, "Time Update Control Point"},
    {0x2a17, "Time Update State"},
    {0x2a18, "Glucose Measurement"},
    {0x2a19, "Battery Level"},
    /* 0x2a1a and 0x2a1b undefined */
    {0x2a1c, "Temperature Measurement"},
    {0x2a1d, "Temperature Type"},
    {0x2a1e, "Intermediate Temperature"},
    /* 0x2a1f and 0x2a20 undefined */
    {0x2a21, "Measurement Interval"},
    {0x2a22, "Boot Keyboard Input Report"},
    {0x2a23, "System ID"},
    {0x2a24, "Model Number String"},
    {0x2a25, "Serial Number String"},
    {0x2a26, "Firmware Revision String"},
    {0x2a27, "Hardware Revision String"},
    {0x2a28, "Software Revision String"},
    {0x2a29, "Manufacturer Name String"},
    {0x2a2a, "IEEE 11073-20601 Regulatory Cert. Data List"},
    {0x2a2b, "Current Time"},
    {0x2a2c, "Magnetic Declination"},
    /* 0x2a2d to 0x2a30 undefined */
    {0x2a31, "Scan Refresh"},
    {0x2a32, "Boot Keyboard Output Report"},
    {0x2a33, "Boot Mouse Input Report"},
    {0x2a34, "Glucose Measurement Context"},
    {0x2a35, "Blood Pressure Measurement"},
    {0x2a36, "Intermediate Cuff Pressure"},
    {0x2a37, "Heart Rate Measurement"},
    {0x2a38, "Body Sensor Location"},
    {0x2a39, "Heart Rate Control Point"},
    /* 0x2a3a to 0x2a3e undefined */
    {0x2a3f, "Alert Status"},
    {0x2a40, "Ringer Control Point"},
    {0x2a41, "Ringer Setting"},
    {0x2a42, "Alert Category ID Bit Mask"},
    {0x2a43, "Alert Category ID"},
    {0x2a44, "Alert Notification Control Point"},
    {0x2a45, "Unread Alert Status"},
    {0x2a46, "New Alert"},
    {0x2a47, "Supported New Alert Category"},
    {0x2a48, "Supported Unread Alert Category"},
    {0x2a49, "Blood Pressure Feature"},
    {0x2a4a, "HID Information"},
    {0x2a4b, "Report Map"},
    {0x2a4c, "HID Control Point"},
    {0x2a4d, "Report"},
    {0x2a4e, "Protocol Mode"},
    {0x2a4f, "Scan Interval Window"},
    {0x2a50, "PnP ID"},
    {0x2a51, "Glucose Feature"},
    {0x2a52, "Record Access Control Point"},
    {0x2a53, "RSC Measurement"},
    {0x2a54, "RSC Feature"},
    {0x2a55, "SC Control Point"},
    {0x2a56, "Digital"},
    /* 0x2a57 undefined */
    {0x2a58, "Analog"},
    /* 0x2a59 undefined */
    {0x2a5a, "Aggregate"},
    {0x2a5b, "CSC Measurement"},
    {0x2a5c, "CSC Feature"},
    {0x2a5d, "Sensor Location"},
    /* 0x2a5e to 0x2a62 undefined */
    {0x2a63, "Cycling Power Measurement"},
    {0x2a64, "Cycling Power Vector"},
    {0x2a65, "Cycling Power Feature"},
    {0x2a66, "Cycling Power Control Point"},
    {0x2a67, "Location and Speed"},
    {0x2a68, "Navigation"},
    {0x2a69, "Position Quality"},
    {0x2a6a, "LN Feature"},
    {0x2a6b, "LN Control Point"},
    {0x2a6c, "Elevation"},
    {0x2a6d, "Pressure"},
    {0x2a6e, "Temperature"},
    {0x2a6f, "Humidity"},
    {0x2a70, "True Wind Speed"},
    {0x2a71, "True Wind Direction"},
    {0x2a72, "Apparent Wind Speed"},
    {0x2a73, "Apparent Wind Direction"},
    {0x2a74, "Gust Factor"},
    {0x2a75, "Pollen Concentration"},
    {0x2a76, "UV Index"},
    {0x2a77, "Irradiance"},
    {0x2a78, "Rainfall"},
    {0x2a79, "Wind Chill"},
    {0x2a7a, "Heat Index"},
    {0x2a7b, "Dew Point"},
    {0x2a7c, "Trend"},
    {0x2a7d, "Descriptor Value Changed"},
    {0x2a7e, "Aerobic Heart Rate Lower Limit"},
    {0x2a7f, "Aerobic Threshold"},
    {0x2a80, "Age"},
    {0x2a81, "Anaerobic Heart Rate Lower Limit"},
    {0x2a82, "Anaerobic Heart Rate Upper Limit"},
    {0x2a83, "Anaerobic Threshold"},
    {0x2a84, "Aerobic Heart Rate Upper Limit"},
    {0x2a85, "Date of Birth"},
    {0x2a86, "Date of Threshold Assessment"},
    {0x2a87, "Email Address"},
    {0x2a88, "Fat Burn Heart Rate Lower Limit"},
    {0x2a89, "Fat Burn Heart Rate Upper Limit"},
    {0x2a8a, "First Name"},
    {0x2a8b, "Five Zone Heart Rate Limits"},
    {0x2a8c, "Gender"},
    {0x2a8d, "Heart Rate Max"},
    {0x2a8e, "Height"},
    {0x2a8f, "Hip Circumference"},
    {0x2a90, "Last Name"},
    {0x2a91, "Maximum Recommended Heart Rate"},
    {0x2a92, "Resting Heart Rate"},
    {0x2a93, "Sport Type for Aerobic/Anaerobic Thresholds"},
    {0x2a94, "Three Zone Heart Rate Limits"},
    {0x2a95, "Two Zone Heart Rate Limit"},
    {0x2a96, "VO2 Max"},
    {0x2a97, "Waist Circumference"},
    {0x2a98, "Weight"},
    {0x2a99, "Database Change Increment"},
    {0x2a9a, "User Index"},
    {0x2a9b, "Body Composition Feature"},
    {0x2a9c, "Body Composition Measurement"},
    {0x2a9d, "Weight Measurement"},
    {0x2a9e, "Weight Scale Feature"},
    {0x2a9f, "User Control Point"},
    {0x2aa0, "Magnetic Flux Density - 2D"},
    {0x2aa1, "Magnetic Flux Density - 3D"},
    {0x2aa2, "Language"},
    {0x2aa3, "Barometric Pressure Trend"},
    {0x2aa4, "Bond Management Control Point"},
    {0x2aa5, "Bond Management Feature"},
    {0x2aa6, "Central Address Resolution"},
    {0x2aa7, "CGM Measurement"},
    {0x2aa8, "CGM Feature"},
    {0x2aa9, "CGM Status"},
    {0x2aaa, "CGM Session Start Time"},
    {0x2aab, "CGM Session Run Time"},
    {0x2aac, "CGM Specific Ops Control Point"},
    {0x2aad, "Indoor Positioning Configuration"},
    {0x2aae, "Latitude"},
    {0x2aaf, "Longitude"},
    {0x2ab0, "Local North Coordinate"},
    {0x2ab1, "Local East Coordinate"},
    {0x2ab2, "Floor Number"},
    {0x2ab3, "Altitude"},
    {0x2ab4, "Uncertainty"},
    {0x2ab5, "Location Name"},
    {0x2ab6, "URI"},
    {0x2ab7, "HTTP Headers"},
    {0x2ab8, "HTTP Status Code"},
    {0x2ab9, "HTTP Entity Body"},
    {0x2aba, "HTTP Control Point"},
    {0x2abb, "HTTPS Security"},
    {0x2abc, "TDS Control Point"},
    {0x2abd, "OTS Feature"},
    {0x2abe, "Object Name"},
    {0x2abf, "Object Type"},
    {0x2ac0, "Object Size"},
    {0x2ac1, "Object First-Created"},
    {0x2ac2, "Object Last-Modified"},
    {0x2ac3, "Object ID"},
    {0x2ac4, "Object Properties"},
    {0x2ac5, "Object Action Control Point"},
    {0x2ac6, "Object List Control Point"},
    {0x2ac7, "Object List Filter"},
    {0x2ac8, "Object Changed"},
    /* vendor defined */
    {0xfeff, "GN Netcom"},
    {0xfefe, "GN ReSound A/S"},
    {0xfefd, "Gimbal, Inc."},
    {0xfefc, "Gimbal, Inc."},
    {0xfefb, "Stollmann E+V GmbH"},
    {0xfefa, "PayPal, Inc."},
    {0xfef9, "PayPal, Inc."},
    {0xfef8, "Aplix Corporation"},
    {0xfef7, "Aplix Corporation"},
    {0xfef6, "Wicentric, Inc."},
    {0xfef5, "Dialog Semiconductor GmbH"},
    {0xfef4, "Google"},
    {0xfef3, "Google"},
    {0xfef2, "CSR"},
    {0xfef1, "CSR"},
    {0xfef0, "Intel"},
    {0xfeef, "Polar Electro Oy"},
    {0xfeee, "Polar Electro Oy"},
    {0xfeed, "Tile, Inc."},
    {0xfeec, "Tile, Inc."},
    {0xfeeb, "Swirl Networks, Inc."},
    {0xfeea, "Swirl Networks, Inc."},
    {0xfee9, "Quintic Corp."},
    {0xfee8, "Quintic Corp."},
    {0xfee7, "Tencent Holdings Limited"},
    {0xfee6, "Seed Labs, Inc."},
    {0xfee5, "Nordic Semiconductor ASA"},
    {0xfee4, "Nordic Semiconductor ASA"},
    {0xfee3, "Anki, Inc."},
    {0xfee2, "Anki, Inc."},
    {0xfee1, "Anhui Huami Information Technology Co."},
    {0xfee0, "Anhui Huami Information Technology Co."},
    {0xfedf, "Design SHIFT"},
    {0xfede, "Coin, Inc."},
    {0xfedd, "Jawbone"},
    {0xfedc, "Jawbone"},
    {0xfedb, "Perka, Inc."},
    {0xfeda, "ISSC Technologies Corporation"},
    {0xfed9, "Pebble Technology Corporation"},
    {0xfed8, "Google"},
    {0xfed7, "Broadcom Corporation"},
    {0xfed6, "Broadcom Corporation"},
    {0xfed5, "Plantronics Inc."},
    {0xfed4, "Apple, Inc."},
    {0xfed3, "Apple, Inc."},
    {0xfed2, "Apple, Inc."},
    {0xfed1, "Apple, Inc."},
    {0xfed0, "Apple, Inc."},
    {0xfecf, "Apple, Inc."},
    {0xfece, "Apple, Inc."},
    {0xfecd, "Apple, Inc."},
    {0xfecc, "Apple, Inc."},
    {0xfecb, "Apple, Inc."},
    {0xfeca, "Apple, Inc."},
    {0xfec9, "Apple, Inc."},
    {0xfec8, "Apple, Inc."},
    {0xfec7, "Apple, Inc."},
    {0xfec6, "Kocomojo, LLC"},
    {0xfec5, "Realtek Semiconductor Corp."},
    {0xfec4, "PLUS Location Systems"},
    {0xfec3, "360fly, Inc."},
    {0xfec2, "Blue Spark Technologies, Inc."},
    {0xfec1, "KDDI Corporation"},
    {0xfec0, "KDDI Corporation"},
    {0xfebf, "Nod, Inc."},
    {0xfebe, "Bose Corporation"},
    {0xfebd, "Clover Network, Inc."},
    {0xfebc, "Dexcom, Inc."},
    {0xfebb, "adafruit industries"},
    {0xfeba, "Tencent Holdings Limited"},
    {0xfeb9, "LG Electronics"},
    {0xfeb8, "Facebook, Inc."},
    {0xfeb7, "Facebook, Inc."},
    {0xfeb6, "Vencer Co, Ltd"},
    {0xfeb5, "WiSilica Inc."},
    {0xfeb4, "WiSilica Inc."},
    {0xfeb3, "Taobao"},
    {0xfeb2, "Microsoft Corporation"},
    {0xfeb1, "Electronics Tomorrow Limited"},
    {0xfeb0, "Nest Labs Inc."},
    {0xfeaf, "Nest Labs Inc."},
    {0xfeae, "Nokia Corporation"},
    {0xfead, "Nokia Corporation"},
    {0xfeac, "Nokia Corporation"},
    {0xfeab, "Nokia Corporation"},
    {0xfeaa, "Google"},
    {0xfea9, "Savant Systems LLC"},
    {0xfea8, "Savant Systems LLC"},
    {0xfea7, "UTC Fire and Security"},
    {0xfea6, "GoPro, Inc."},
    {0xfea5, "GoPro, Inc."},
    {0xfea4, "Paxton Access Ltd"},
    {0xfea3, "ITT Industries"},
    {0xfea2, "Intrepid Control Systems, Inc."},
    {0xfea1, "Intrepid Control Systems, Inc."},
    {0xfea0, "Google"},
    {0xfe9f, "Google"},
    {0xfe9e, "Dialog Semiconductor B.V."},
    {0xfe9d, "Mobiquity Networks Inc"},
    {0xfe9c, "GSI Laboratories, Inc."},
    {0xfe9b, "Samsara Networks, Inc"},
    {0xfe9a, "Estimote"},
    {0xfe99, "Currant, Inc."},
    {0xfe98, "Currant, Inc."},
    {0xfe97, "Tesla Motor Inc."},
    {0xfe96, "Tesla Motor Inc."},
    {0xfe95, "Xiaomi Inc."},
    {0xfe94, "OttoQ Inc."},
    {0xfe93, "OttoQ Inc."},
    {0xfe92, "Jarden Safety & Security"},
    {0xfe91, "Shanghai Imilab Technology Co.,Ltd"},
    {0xfe90, "JUMA"},
    {0xfe8f, "CSR"},
    {0xfe8e, "ARM Ltd"},
    {0xfe8d, "Interaxon Inc."},
    {0xfe8c, "TRON Forum"},
    {0xfe8b, "Apple, Inc."},
    {0xfe8a, "Apple, Inc."},
    {0xfe89, "B&O Play A/S"},
    {0xfe88, "SALTO SYSTEMS S.L."},
    {0xfe87,
     "Qingdao Yeelink Information Technology Co., Ltd. ( 青岛亿联客信息技术有限公司 )"},
    {0xfe86, "HUAWEI Technologies Co., Ltd. ( 华为技术有限公司 )"},
    {0xfe85, "RF Digital Corp"},
    {0xfe84, "RF Digital Corp"},
    {0xfe83, "Blue Bite"},
    {0xfe82, "Medtronic Inc."},
    {0xfe81, "Medtronic Inc."},
    {0xfe80, "Doppler Lab"},
    {0xfe7f, "Doppler Lab"},
    {0xfe7e, "Awear Solutions Ltd"},
    {0xfe7d, "Aterica Health Inc."},
    {0xfe7c, "Stollmann E+V GmbH"},
    {0xfe7b, "Orion Labs, Inc."},
    /* SDO defined */
    {0xfffe, "Alliance for Wireless Power (A4WP)"},
    {0xfffd, "Fast IDentity Online Alliance (FIDO)"},
    /*TI sensor Tag defined */
    {0xAA01, "IR Temperature Data"},
    {0xAA02, "IR Temperature Config"},
    {0xAA03, "IR Temperature Period"},
    {0xAA11, "Accelerometer Data"},
    {0xAA12, "Accelerometer Config"},
    {0xAA13, "Accelerometer Period"},
    {0xAA21, "Humidity Data"},
    {0xAA22, "Humidity Config"},
    {0xAA23, "Humidity Period"},
    {0xAA31, "Magnetometer Data"},
    {0xAA32, "Magnetometer Config"},
    {0xAA33, "Magnetometer Period"},
    {0xAA41, "Barometer Data"},
    {0xAA42, "Barometer Configuration"},
    {0xAA44, "Barometer period"},
    {0xAA43, "Barometer Calibration"},
    {0xAA51, "Gyroscope Data"},
    {0xAA52, "Gyroscope Config"},
    {0xAA53, "Gyroscope Period"},
    {0xAA61, "Test Data"},
    {0xAA62, "Test Config"},
    {0xCCC1, "Connection Parameters"},
    {0xCCC2, "Request Connection Parameters"},
    {0xCCC3, "Disconnect request"},
    {0xFFC1, "OAD Image Identify"},
    {0xFFC2, "OAD Image Block"},
    {0xFFE1, "simple key service"},
    {}
};
////////////////////
/*.............................................................................*/
void terminateListofDevices(void) {
    NonIotivity_BLE_Device_InfoTable.ucNumOfDevices = 0 ;
    obs_table_index = 0;
    pthread_mutex_unlock(&mutex_lock_noniot);
    return;
}

/*.............................................................................*/
key_value_pair_t1 *Observe(char *addr)
{
    for(int i2 = 0; i2 < obs_table_index; i2++) {
        if(strcasecmp(addr, obs_table[i2].mac_id)==0) {
            printf("already registered for observe \n");
            return NULL;
        }
    }
    strcpy(obs_table[obs_table_index].mac_id,addr);
    printf("Subscribed to observe notifications from resource: %s\n", obs_table[obs_table_index].mac_id);
    printf("  obs_table_index = %d\n", obs_table_index);
    obs_table_index++;
    return NULL;
}
/*.............................................................................*/

int32_t NonIotivity_Get_Table_Index_By_UUID (uint16_t hnd, int32_t index_val)
{
    int32_t i;
    if(index_val < NI_table_index) {
        for (i = index_val; i < NI_table_index; i++) {
            if ((NI_characteristic_table[i].type[12] == (hnd & 0xff))
                    && (NI_characteristic_table[i].type[13] == ((hnd >> 8) & 0xff))) {
                return i;
            }
        }
    }
    return 0xffff;
}
/*.............................................................................*/
int32_t NonIotivity_Get_Handle_By_Index (uint16_t index)
{
    int32_t i;
    for (i = 0; i < NI_table_index; i++) {
        if (i == index) {
            return NI_characteristic_table[i].handle;
        }
    }
    return 0xffff;
}
/*.............................................................................*/
int32_t NonIotivity_Get_Index_By_Handle (uint16_t hnd)
{
    int32_t i;
    for (i = 0; i < NI_table_index; i++) {
        if (NI_characteristic_table[i].handle == hnd){
            return i;
        }
    }
    return 0xffff;
}
/*.............................................................................*/
int8_t *NonIotivity_UUID_To_String (uint16_t uuid)
{
    int32_t i;
    for (i = 0; i < (sizeof (uuid_table) / sizeof (uuid_table_t)); i++) {
        if (uuid_table[i].uuid == uuid){
            return uuid_table[i].str;
        }
    }
    return "Unknown";
}
/*.............................................................................*/
key_value_pair_t1 *NonIotivity_Form_Key_Value_Pair(int32_t fd, info* tbl)
{
    int32_t index = 0;
    int32_t i;
    int32_t primary_index;
    int32_t nCharIndex;
    int32_t key_value_pair_index;
    unsigned char wpdu[512];
    unsigned char rpdu[512];
    key_value_pair_t1 *NI_pKeyValue_Global = NULL;
    key_value_pair_t1 *pKeyValue_LocalNode = NULL;
    key_value_pair_t1 *pKeyValue_Temp = NULL;
    uint8_t *pcKey = NULL;
    uint16_t attr_handle;
    uint16_t test_uuid;
    uint32_t len = 0;
    uint32_t size = 0;
    int32_t j,l;
    uint8_t temp[512];

    while ((primary_index = NonIotivity_Get_Table_Index_By_UUID (0x2800, index)) != 0xffff) {
        nCharIndex = NonIotivity_Get_Table_Index_By_UUID (0x2803, primary_index);
        attr_handle = NonIotivity_Get_Handle_By_Index(nCharIndex) + 1 ;
        key_value_pair_index = NonIotivity_Get_Index_By_Handle (attr_handle);
        wpdu[0] = BT_ATT_OP_READ_REQ;
        wpdu[1] = attr_handle & 0xff;
        wpdu[2] = (attr_handle & 0xff00) >> 8;

        size = write (fd, wpdu, 3);
        len = read (fd, rpdu, 512);
        if(rpdu[0] == ATT_OP_HANDLE_NOTIFY){
            read (fd, rpdu, 512);
        }

        memset (tbl[key_value_pair_index].value, 0, sizeof(tbl[key_value_pair_index].value));
        memcpy (tbl[key_value_pair_index].value, rpdu+1, len-1);

        if(key_value_pair_index == 0xffff) {
            printf("index not found\n");
            index = nCharIndex;
            continue;
        }
        pKeyValue_LocalNode = (key_value_pair_t1*) malloc (sizeof (key_value_pair_t1));
        pKeyValue_LocalNode->pNext = NULL;
        test_uuid = tbl[key_value_pair_index].type[13] << 8 | tbl[key_value_pair_index].type[12];
        pcKey = NonIotivity_UUID_To_String (test_uuid);
        strcpy (pKeyValue_LocalNode->key, pcKey);
        memcpy (pKeyValue_LocalNode->value, tbl[key_value_pair_index].value, 512);
        if(strcmp(pKeyValue_LocalNode->key,"Device Name") == 0) {
            //none
            for (i=0; i<20;i++) {
                //                printf("%c",pKeyValue_LocalNode->value[i]);
            }
        }
        else {
            if(pKeyValue_LocalNode->value[1] == NULL) {
                strcpy(pKeyValue_LocalNode->value, "NULL");
                //                printf(" :%s", pKeyValue_LocalNode->value);
            }
            else {
                for (i=0; i<20;i++) {
                    //                    printf("%.2X ",pKeyValue_LocalNode->value[i]);
                }
                j = 0;
                memset(temp,'\0',512);
                for (l=0; l<20;l++) {
                    sprintf(&temp[j],"%.2X ",pKeyValue_LocalNode->value[l]);
                    j=j+3;
                }
                strncpy(pKeyValue_LocalNode->value, temp, strlen(temp));
            }
        }
        pKeyValue_LocalNode->handle_res = tbl[key_value_pair_index].handle;
        pKeyValue_Temp = NI_pKeyValue_Global;
        if (NI_pKeyValue_Global == NULL) {
            NI_pKeyValue_Global = pKeyValue_LocalNode;
        }
        else {
            while (pKeyValue_Temp->pNext != NULL) {
                pKeyValue_Temp = pKeyValue_Temp->pNext;
            }
            pKeyValue_Temp->pNext = pKeyValue_LocalNode;
            pKeyValue_LocalNode = NULL;
            free(pKeyValue_LocalNode);
        }
        index = nCharIndex;
    }
    return NI_pKeyValue_Global;
}
/*.......................................................................*/
key_value_pair_t1 *NonIotivity_Form_Key_Value_Pair_Put(int32_t fd, info* tbl)
{
    int32_t index = 0;
    int32_t i;
    int32_t primary_index;
    int32_t nCharIndex;
    int32_t key_value_pair_index;
    unsigned char wpdu[512];
    unsigned char rpdu[512];
    key_value_pair_t1 *NI_pKeyValue_Global = NULL;
    key_value_pair_t1 *pKeyValue_LocalNode = NULL;
    key_value_pair_t1 *pKeyValue_Temp = NULL;
    uint8_t *pcKey = NULL;
    uint16_t attr_handle;
    uint16_t test_uuid;
    uint32_t len = 0;
    uint32_t size = 0;
    int32_t j,l;
    uint8_t temp[512];
/*s*/
    int32_t fd_c;
    unsigned char wpdu_c[512];
    unsigned char rpdu_c[512];
    uint32_t len_c = 0;
    uint32_t size_c = 0;
    uint16_t char_handle;
/*e*/
    while ((primary_index = NonIotivity_Get_Table_Index_By_UUID (0x2800, index)) != 0xffff) {
        nCharIndex = NonIotivity_Get_Table_Index_By_UUID (0x2803, primary_index);
/*s*/
        char_handle = NonIotivity_Get_Handle_By_Index(nCharIndex);
        memset(wpdu_c, '\0', 512);
        memset(rpdu_c, '\0', 512);
        wpdu_c[0] = BT_ATT_OP_READ_REQ;
        wpdu_c[1] = char_handle & 0xff;
        wpdu_c[2] = (char_handle & 0xff00) >> 8;
        fd_c = fd;
        size_c = write (fd_c, wpdu_c, 3);
        len_c = read (fd_c, rpdu_c, 512);
//        for(int g=0; g<len_c; g++)
//             {
//             printf("*** rpdu_c[%d]= %.2x \n",g,rpdu_c[g]);
//             }
/*e*/
        attr_handle = NonIotivity_Get_Handle_By_Index(nCharIndex) + 1 ;
        key_value_pair_index = NonIotivity_Get_Index_By_Handle (attr_handle);

        wpdu[0] = BT_ATT_OP_READ_REQ;
        wpdu[1] = attr_handle & 0xff;
        wpdu[2] = (attr_handle & 0xff00) >> 8;

        size = write (fd, wpdu, 3);
        len = read (fd, rpdu, 512);
        if(rpdu[0] == ATT_OP_HANDLE_NOTIFY){
            read (fd, rpdu, 512);
        }

        memset (tbl[key_value_pair_index].value, 0, sizeof(tbl[key_value_pair_index].value));
        memcpy (tbl[key_value_pair_index].value, rpdu+1, len-1);

        if(key_value_pair_index == 0xffff) {
            printf("index not found\n");
            index = nCharIndex;
            continue;
        }
        pKeyValue_LocalNode = (key_value_pair_t1*) malloc (sizeof (key_value_pair_t1));
        pKeyValue_LocalNode->pNext = NULL;

        pKeyValue_LocalNode->permissions = rpdu_c[1];

        test_uuid = tbl[key_value_pair_index].type[13] << 8 | tbl[key_value_pair_index].type[12];
        pcKey = NonIotivity_UUID_To_String (test_uuid);
        strcpy (pKeyValue_LocalNode->key, pcKey);
        memcpy (pKeyValue_LocalNode->value, tbl[key_value_pair_index].value, 512);
        if(strcmp(pKeyValue_LocalNode->key,"Device Name") == 0) {
            //none
            for (i=0; i<20;i++) {
                //                printf("%c",pKeyValue_LocalNode->value[i]);
            }
        }
        else {
            if(pKeyValue_LocalNode->value[1] == NULL) {
                strcpy(pKeyValue_LocalNode->value, "NULL");
                //                printf(" :%s", pKeyValue_LocalNode->value);
            }
            else {
                for (i=0; i<20;i++) {
                    //                    printf("%.2X ",pKeyValue_LocalNode->value[i]);
                }
                j = 0;
                memset(temp,'\0',512);
                for (l=0; l<20;l++) {
                    sprintf(&temp[j],"%.2X ",pKeyValue_LocalNode->value[l]);
                    j=j+3;
                }
                strncpy(pKeyValue_LocalNode->value, temp, strlen(temp));
            }
        }
        pKeyValue_LocalNode->handle_res = tbl[key_value_pair_index].handle;
        pKeyValue_Temp = NI_pKeyValue_Global;
        if (NI_pKeyValue_Global == NULL) {
            NI_pKeyValue_Global = pKeyValue_LocalNode;
        }
        else {
            while (pKeyValue_Temp->pNext != NULL) {
                pKeyValue_Temp = pKeyValue_Temp->pNext;
            }
            pKeyValue_Temp->pNext = pKeyValue_LocalNode;
            pKeyValue_LocalNode = NULL;
            free(pKeyValue_LocalNode);
        }
        index = nCharIndex;
    }
    return NI_pKeyValue_Global;
}

/*.............................................................................*/
void NonIotivity_Write_To_Char_Table (int32_t fd, int8_t start[], int8_t stop[])
{
    uint8_t wpdu[512];
    uint8_t rpdu[512];
    uint32_t len = 0;
    uint32_t i = 0, j = 0;
    uint32_t size = 0;
    uint16_t last_handle;
    wpdu[0] = BT_ATT_OP_FIND_INFO_REQ;
    wpdu[1] = start[1];
    wpdu[2] = start[0];
    wpdu[3] = stop[1];
    wpdu[4] = stop[0];
    last_handle = start[1] | (start[0] << 8);
    len = 0;
    memset(NI_characteristic_table,0,sizeof(NI_characteristic_table));
    NI_table_index = 0;
    while (last_handle != 0xffff) {
        wpdu[1] = last_handle & 0xff;
        wpdu[2] = (last_handle & 0xff00) >> 8;
        size = write (fd, wpdu, 5);
        len = read (fd, rpdu, 512);
        if (rpdu[0] != BT_ATT_OP_ERROR_RSP) {
            if (rpdu[1] == 0x01) {
                for (i = 0; i < ((len - 2) / 4); i++) {
                    j = (4 * i) + 2;
                    NI_characteristic_table[NI_table_index].handle = (rpdu[j + 1] << 8) | rpdu[j + 0];
                    NI_characteristic_table[NI_table_index].type[13] = rpdu[j + 3];
                    NI_characteristic_table[NI_table_index].type[12] = rpdu[j + 2];
                    NI_characteristic_table[NI_table_index].type_uuid = 0x01;
                    last_handle = NI_characteristic_table[NI_table_index].handle + 1;
                    NI_table_index++;
                }
            }
            else if (rpdu[1] == 0x02) {
                for (i = 0; i < ((len - 2) / 18); i++) {
                    j = (i * 18) + 2;
                    NI_characteristic_table[NI_table_index].handle = rpdu[j + 1] << 8 | rpdu[j + 0];
                    memcpy (NI_characteristic_table[NI_table_index].type, &rpdu[j + 2], 16);
                    NI_characteristic_table[NI_table_index].type_uuid = 0x02;
                    last_handle = NI_characteristic_table[NI_table_index].handle + 1;
                    NI_table_index++;
                }
            }
        }
        else {
            return ;
        }
    }
    return ;
}

/*.............................................................................*/
static int32_t NonIotivity_L2cap_Le_Att_Connect(bdaddr_t *src, bdaddr_t *dst,
                                                uint8_t dst_type, int32_t sec)
{
    int32_t sock;
    struct sockaddr_l2 srcaddr, dstaddr;
    struct bt_security btsec;
    static bool NI_verbose = false;

    if (NI_verbose) {
        int8_t srcaddr_str[18], dstaddr_str[18];
        ba2str(src, srcaddr_str);
        ba2str(dst, dstaddr_str);
    }
    sock = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
    if (sock < 0) {
        perror("Failed to create L2CAP socket");
        return -1;
    }

    /* Set up source address */
    memset(&srcaddr, 0, sizeof(srcaddr));
    srcaddr.l2_family = AF_BLUETOOTH;
    srcaddr.l2_cid = htobs(ATT_CID);
    srcaddr.l2_bdaddr_type = 0;
    bacpy(&srcaddr.l2_bdaddr, src);

    if (bind(sock, (struct sockaddr *)&srcaddr, sizeof(srcaddr)) < 0) {
        perror("Failed to bind L2CAP socket");
        close(sock);
        return -1;
    }

    /* Set the security level */
    memset(&btsec, 0, sizeof(btsec));
    btsec.level = sec;
    if (setsockopt(sock, SOL_BLUETOOTH, BT_SECURITY, &btsec,
                   sizeof(btsec)) != 0) {
        fprintf(stderr, "Failed to set L2CAP security level\n");
        close(sock);
        return -1;
    }

    /* Set up destination address */
    memset(&dstaddr, 0, sizeof(dstaddr));
    dstaddr.l2_family = AF_BLUETOOTH;
    dstaddr.l2_cid = htobs(ATT_CID);
    dstaddr.l2_bdaddr_type = dst_type;
    bacpy(&dstaddr.l2_bdaddr, dst);

    printf("Connecting to device...");
    //fflush(stdout);

    if (connect(sock, (struct sockaddr *) &dstaddr, sizeof(dstaddr)) < 0) {
        //perror(" Failed to connect");
        close(sock);
        return -1;
    }
    printf(" Done\n");
    return sock;
}

/*.............................................................................*/
void NonIotivity_Mtu_Request(int32_t fd)
{
    uint8_t wpdu[512];
    uint8_t rpdu[512];
    uint32_t size=0;

    wpdu[0] = BT_ATT_OP_MTU_REQ;
    wpdu[1] = 0x00;
    wpdu[2] = 0x01;

    size = write(fd, wpdu, 3);
    sleep(1);
    read(fd, rpdu, 512);
    return ;
}
/*.............................................................................*/
int32_t NonIotivity_Connect(int8_t* dst_address)

{
    int32_t sec = BT_SECURITY_LOW;
    uint8_t dst_type = BDADDR_LE_PUBLIC;
    bdaddr_t src_addr, dst_addr;
    int32_t dev_id = -1;
    int32_t fd;
    int32_t NI_write_done;

    if(str2ba(dst_address, &dst_addr) < 0) {
        perror("Invalid remote address:\n");
        return -1;
    }

    if(dev_id == -1) {
        bacpy(&src_addr, BDADDR_ANY);
    }
    else if (hci_devba(dev_id, &src_addr) < 0) {
        perror("Adapter not available");
        return -1;
    }

    fd = NonIotivity_L2cap_Le_Att_Connect(&src_addr, &dst_addr, dst_type, sec);
    if(fd < 0) {
        return -1;
    }
    NI_write_done = 0;
    NonIotivity_Mtu_Request(fd);
    NonIotivity_Enable_Notification(fd);
    return fd;
}
//*******************VITA_DM******************************
/*.............................................................................*/
void NonIotivity_Write_Request(int32_t file_descriptor,  uint8_t *data,  uint8_t length)
{
    uint8_t rpdu[512];
    int32_t fd = file_descriptor;
    uint8_t len;

    len = write(file_descriptor, data, length);
    if(len != length) {
        //printf(" Write Failure\n");
        len = write(fd, data, length);
    }
    sleep(1);
    while(1) {
        len = read(file_descriptor, rpdu, 512);
        break;
    }
    return ;
}

/*.............................................................................*/
void NonIotivity_Enable_Notification(int32_t fd)
{
    uint8_t wpdu[512];
    wpdu[0] = BT_ATT_OP_WRITE_REQ;
    wpdu[1] = 0x10;
    wpdu[2] = 0x00;
    wpdu[3] = 0x01;
    wpdu[4] = 0x00;

    NonIotivity_Write_Request(fd, wpdu, 5);
    sleep(1);
    return ;
}
/*.............................................................................*/
void NonIoTivity_Init (void)
{
    int result = 0;
    pthread_t thread_id;
    memset (&NonIotivity_BLE_Device_InfoTable, 0, sizeof (NonIotivity_BLE_Device_InfoTable));
    NonIotivity_BLE_Device_InfoTable.ucNumOfDevices = 0;
    /*------------------------thread creation------------------------*/
    result = pthread_create(&thread_id, NULL, &client_observe, NULL);
    printf("result: %d \n", result);
    if(result!=0)
    {
        printf("Error in creating pthread for client observe\n");
        exit(1);
    }
    else
        printf("Thread created for client observe\n");
    /*----------------------------------------------------------------*/
}
/*.............................................................................*/
uint8_t* NonIoTivity_AddDevice (uint8_t *ucpMacId, uint8_t *ucpDeviceName) {
    int8_t Non_Iot_dev_name[100];
    int32_t i;
    sprintf(Non_Iot_dev_name, "/non_iotvity-%s", ucpMacId);
    for(i = 0; i < NonIotivity_BLE_Device_InfoTable.ucNumOfDevices; i++) {
        if( strcmp(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[i].ucURI, Non_Iot_dev_name) == 0) {
            return NULL;
        }
    }
    if((ucpDeviceName != NULL))
    {
        if(recievePacketNotify(Non_Iot_dev_name) == 0) {
            memcpy(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[NonIotivity_BLE_Device_InfoTable.ucNumOfDevices].ucMacId, ucpMacId, strlen(ucpMacId));	// Get from Advertisement packet
            memcpy(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[NonIotivity_BLE_Device_InfoTable.ucNumOfDevices].ucDeviceName, ucpDeviceName, strlen((ucpDeviceName)));	// Get from Advertisement packet
            strcpy(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[NonIotivity_BLE_Device_InfoTable.ucNumOfDevices].ucURI, Non_Iot_dev_name); // DeviceName;	// Get from Advertisement packet
            NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[NonIotivity_BLE_Device_InfoTable.ucNumOfDevices].eState = DISCOVERED;
            NonIotivity_BLE_Device_InfoTable.ucNumOfDevices++;
        }
        //return Non_Iot_dev_name;
    }
    return ;
}
/*.............................................................................*/
void NonIotivity_Write_Configure_data(int fd)
{
    unsigned char wpdu[512];
    unsigned char rpdu[512];
    unsigned int len = 0;
    unsigned int i = 0, j = 0;
    unsigned int size = 0;
    uint16_t temp_id;
    len = 0;
    for(i=0;i<NI_table_index;i++) {
        if(NI_characteristic_table[i].type_uuid == 0x02) {
            temp_id = (NI_characteristic_table[i].type[13]<< 8) | NI_characteristic_table[i].type[12];
            if((temp_id == 0xaa02) ||
                    (temp_id == 0xaa12) ||
                    (temp_id == 0xaa22) ||
                    (temp_id == 0xaa32) ||
                    (temp_id == 0xaa42) ||
                    (temp_id == 0xaa52) ||
                    (temp_id == 0xaa62)) {
                // if(temp_id ==  0xaa12){
                wpdu[0] = BT_ATT_OP_WRITE_REQ;
                wpdu[1] = NI_characteristic_table[i].handle & 0xff;
                wpdu[2] = (NI_characteristic_table[i].handle & 0xff00) >> 8;
                wpdu[3] = 0x01;// only one byte writing

                size = write (fd, wpdu, 4);
                len = read (fd, rpdu, 512);
                if((len == 0) &&
                        (BT_ATT_OP_ERROR_RSP == 0)){
                    printf("Write_data failure\n");
                }
                else {
                    // printf("Write_data success\n");
                }
            }
        }
    }
}

/*.............................................................................*/
key_value_pair_t1* NonIoTivity_Get(uint8_t* URI)
{
    key_value_pair_t1 *pairs;
    pthread_mutex_lock(&mutex_lock_noniot);
    pairs = get(URI);
    pthread_mutex_unlock(&mutex_lock_noniot);
    return pairs;
}

/*.............................................................................*/
key_value_pair_t1* get(uint8_t* URI)
{
    int8_t start[2] = { 0x00, 0x01};
    int8_t end[2] = { 0xff, 0xff};
    key_value_pair_t1 *pairs;

    int32_t fd;
    int32_t i;
    for (i = 0; i < NonIotivity_BLE_Device_InfoTable.ucNumOfDevices; i++) {
        if (!strcmp(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[i].ucURI,URI)) {
            break;
        }
    }
    if (i == NonIotivity_BLE_Device_InfoTable.ucNumOfDevices) {
        perror("We don \'t have any device matching URI\n");
    }
    fd = NonIotivity_Connect(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[i].ucMacId);
    if (fd == -1) {
        NI_testGetdata = NULL;
        return NULL;
    }
    NonIotivity_Write_To_Char_Table (fd, start, end);
    NonIotivity_Write_Configure_data(fd);
    pairs = NonIotivity_Form_Key_Value_Pair(fd, NI_characteristic_table);
    NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[i].pJSON = pairs;
    NI_testGetdata = pairs;
    close(fd);
    return pairs;
}

/* COPY A ENTIRE LINKED LIST TO ANOTHER LIST */
key_value_pair_t1 *List_copy(key_value_pair_t1 *list)
{
    static int i;
    key_value_pair_t1  *temp_node = NULL;
    key_value_pair_t1  *head = NULL;
    i=0;
    while(list != NULL) {
        temp_node = (key_value_pair_t1 *)malloc(sizeof(key_value_pair_t1 ));
        memset(temp_node, 0, sizeof(key_value_pair_t1 ));
        memcpy(temp_node, list, sizeof(key_value_pair_t1 ));
        if(i==0) {
            head = temp_node;   //printf("taking head\n");
            i=1;
        }
        list = list->pNext;
        temp_node =  temp_node->pNext;
    }
    return head;
}

void print_list2(key_value_pair_t1 *node)
{
    key_value_pair_t1 *travel_node = NULL;
    travel_node = node;
    while(travel_node != NULL) {
        printf("KEY = %-20s   VALUE = %s\n", travel_node->key, travel_node->value);
        travel_node = travel_node->pNext;
    }
    free(travel_node);
}
/*.............................................................................*/
void *client_observe(void)
{
    int ObserveNotify = 0;
    while(1) {
        for(int i = 0; i < obs_table_index; i++) {
            pthread_mutex_lock(&mutex_lock_noniot);

            unsigned char uri[50];
            static key_value_pair_t1 *temp_pairs = NULL;
            static key_value_pair_t1 *obs_temp_pairs = NULL;
            static key_value_pair_t1 *pairs_d = NULL;

            strcpy(uri,"/non_iotvity-");
            strcat(uri,obs_table[i].mac_id);
            temp_pairs = get(uri);
            sleep(1);
            pairs_d = temp_pairs;

            if(obs_table[i].observe_pair == NULL) {
                obs_table[i].observe_pair = List_copy(temp_pairs);
                sleep(1);
            }
            else {
                while (pairs_d != NULL) {
                    printf("\n");
                    obs_temp_pairs = obs_table[i].observe_pair;
                    while(obs_temp_pairs != NULL) {
                        if((memcmp(pairs_d->key, obs_temp_pairs->key, 28) == 0)) {
                            //                            printf("\n\n");
                            if(memcmp(pairs_d->value, obs_temp_pairs->value, sizeof(pairs_d->value)) != 0)
                            {
                                printf("=======================Change found============================\n");
                                printf("Changed KEY = %-20s   VALUE = %s\n", pairs_d->key, pairs_d->value);
                                printf("        KEY = %-20s   VALUE = %s\n", obs_temp_pairs->key, obs_temp_pairs->value);
                                memcpy(obs_temp_pairs->value, pairs_d->value, sizeof(pairs_d->value));
                                ObserveNotify = 1;
                            }
                            break;
                        }
                        obs_temp_pairs = obs_temp_pairs->pNext;
                    }
                    pairs_d = pairs_d->pNext;
                }
                if(ObserveNotify) {
                    observenotifyData(uri);
                    ObserveNotify = 0;
                }
                else {
                    printf("=======================Change not found============================\n");
                }
                sleep(1);
            }
            pthread_mutex_unlock(&mutex_lock_noniot);
        }
        sleep(2);
    }
}
/*.............................................................................*/
int32_t NonIoTivity_Put (uint8_t* URI, key_value_pair_t1 *json)
{
    pthread_mutex_lock(&mutex_lock_noniot);
    int8_t start[2] = {0x00, 0x01};
    int8_t end[2] = {0xff, 0xff};
    key_value_pair_t1 *pairs_new = NULL;
    key_value_pair_t1 *GetJsonOut;
    int32_t index = 0;
    int32_t fd;
    uint8_t wpdu[512], rpdu[512];
    key_value_pair_t1 *Tempjson;
    key_value_pair_t1 *TempGetJsonOut;
    key_value_pair_t1 *temp_pair;

    Tempjson = json;

    for (index = 0; index < NonIotivity_BLE_Device_InfoTable.ucNumOfDevices; index++){
        if (strcmp(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[index].ucURI,URI) == 0){
            break;
        }
    }

    if (index == (NonIotivity_BLE_Device_InfoTable.ucNumOfDevices))
    {
        perror("We don \'t have any device matching URI for PUT\n");
        printf("We don \'t have any device matching URI for PUT\n");
    }
    printf("Connecting to %s\n", NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[index].ucMacId );

    temp_pair = NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[index].pJSON;
    fd = NonIotivity_Connect(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[index].ucMacId);

    if(fd < 0) {
        printf("NonIoTivity_Put ==> Error at NonIotivity_Connect\n");
        pthread_mutex_unlock(&mutex_lock_noniot);
        return 0;
    }
    NonIotivity_Write_To_Char_Table (fd, start, end);
    pairs_new = NonIotivity_Form_Key_Value_Pair_Put(fd,NI_characteristic_table);
    GetJsonOut = pairs_new;
    while(Tempjson) {
        TempGetJsonOut = GetJsonOut;
        while(TempGetJsonOut != NULL) {
            if(strncmp(Tempjson->key, TempGetJsonOut->key, 28) == 0) {
                if (TempGetJsonOut->permissions == (GATT_CHR_PROP_WRITE) ||
                         TempGetJsonOut->permissions ==(GATT_CHR_PROP_WRITE_WITHOUT_RESP))
                {
                    printf("Characteristic value is writable\n");
                    int32_t len;
                    int32_t value_length;
                    wpdu[0] = BT_ATT_OP_WRITE_REQ;
                    wpdu[1] = TempGetJsonOut->handle_res & 0x00ff;
                    wpdu[2] = (TempGetJsonOut->handle_res &0xff00)>>8;
                    value_length = strlen(Tempjson->value);
                    for(int32_t w = 0; w < value_length; w++) {
                        wpdu[w+3] = (Tempjson->value[w])-48;
                    }
                    len = write(fd, wpdu, value_length+3);
                    if(len == value_length+3){
                        len = -1;
                    }
                    while(len == -1) {
                        memset(rpdu, '\0', 512);
                        len = read(fd, rpdu, 512);
                        if(rpdu[0] == 0x1b){
                            break;
                        }
                        sleep(1);
                    }
                    printf("Put Success.\n");
                }
                else {
                    printf("\n\033[1m\033[31mCharacteristic value is not writable.\033[0m\n");
                    printf("\033[1m\033[31mUnable to put.\033[0m\n");
                    break;
                }

            }
            TempGetJsonOut = TempGetJsonOut->pNext;
        }
        Tempjson = Tempjson->pNext;
    }
    close(fd);
    pthread_mutex_unlock(&mutex_lock_noniot);
    return 1; //success
}
/*.............................................................................*/
#if 0
int32_t connect_device(int8_t *addr)
{

    int32_t sec = BT_SECURITY_LOW;
    uint8_t dst_type = BDADDR_LE_PUBLIC;
    bdaddr_t src_addr, dst_addr;
    int32_t dev_id = -1;
    int32_t fd;
    //if (str2ba (argv[2], &dst_addr) < 0)
    pthread_mutex_lock(&mutex);
    if (str2ba (addr, &dst_addr) < 0) {
        perror ("Invalid remote address:\n");
        return -1;
    }

    if (dev_id == -1) {
        bacpy (&src_addr, BDADDR_ANY);
    }
    else if (hci_devba (dev_id, &src_addr) < 0) {
        perror ("Adapter not available");config
                return -1;
    }

    fd = NonIotivity_L2cap_Le_Att_Connect (&src_addr, &dst_addr, dst_type, sec);
    pthread_mutex_unlock(&mutex);
    return fd;
}
/*.............................................................................*/
#endif

/*.............................................................................*/
void observe_cancel(unsigned char *addr) {
    if(obs_table_index != 0) {
        for(int i = 0; i < obs_table_index; i++) {
            if(strcmp(addr, obs_table[i].mac_id) == 0) {
                memset(obs_table[i].observe_pair, 0, sizeof(key_value_pair_t1));
                obs_table[i] = obs_table[i+1];
                obs_table_index--;
                printf("stoping notifications from observer : %s", addr);
            }
        }
    }
    else
    {
        printf("No client is registered to observe\n");
    }
}
/*.............................................................................*/
key_value_pair_t1* NonIotivity_observe(char * URI, int input) {
    pthread_mutex_lock(&mutex_lock_noniot);
    int i;
    for (i = 0; i < NonIotivity_BLE_Device_InfoTable.ucNumOfDevices; i++) {
        if (!strcmp(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[i].ucURI,URI)) {
            break;
        }
    }
    if (i == NonIotivity_BLE_Device_InfoTable.ucNumOfDevices) {
        perror("We don \'t have any device matching URI\n");
    }
    if (input == 1) {
        Observe(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[i].ucMacId);
    }
    else if(input == 0){
        observe_cancel(NonIotivity_BLE_Device_InfoTable.BLE_DeviceInfo[i].ucMacId);
    }
    pthread_mutex_unlock(&mutex_lock_noniot);
}

/*.............................................................................*/
/*****************************************************************************
 * NOTES:
 *
 *
 *
 *
 *
 *
 *
 *
 */


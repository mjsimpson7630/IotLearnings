/* WiFi Example
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "esp8266-driver/ESP8266Interface.h"
#include "mbed.h"
#include "TCPSocket.h"
//Text 53.6KB Data 2.61KB BSS 7.14KB                 ROM 56.2KB RAM 9.75KB

//+--------------------+-------+-------+------+
//| Module             | .text | .data | .bss |
//+--------------------+-------+-------+------+
//| Fill               |    61 |     4 |   13 |
//| Misc               | 35742 |  2484 |  133 |
//| hal                |   614 |     0 |    8 |
//| platform           |  1809 |     4 |  269 |
//| rtos               |    78 |     4 |    4 |
//| rtos/rtx           | 10163 |    20 | 6326 |
//| targets/TARGET_STM | 11495 |     4 |  723 |
//| Subtotals          | 59962 |  2520 | 7476 |
//+--------------------+-------+-------+------+
//Allocated Heap: unknown
//Allocated Stack: unknown
//Total Static RAM memory (data + bss): 9996 bytes
//Total RAM memory (data + bss + heap + stack): 9996 bytes
//Total Flash memory (text + data + misc): 62482 bytes

ESP8266Interface wifi(D1, D0);	// operator new[] out of memory
//+--------------------+--------+-------+------+
//| Module             |  .text | .data | .bss |
//+--------------------+--------+-------+------+
//| Fill               |    171 |     3 |   17 |
//| Misc               |  73566 |  2500 |  689 |
//| drivers            |   1436 |     0 |    0 |
//| features/netsocket |   5950 |    85 |    0 |
//| hal                |    648 |     0 |    8 |
//| platform           |   2265 |     4 |  269 |
//| rtos               |    407 |     4 |    4 |
//| rtos/rtx           |  11753 |    20 | 6326 |
//| targets/TARGET_STM |  12283 |     4 |  747 |
//| Subtotals          | 108479 |  2620 | 8060 |
//+--------------------+--------+-------+------+
//Allocated Heap: unknown
//Allocated Stack: unknown
//Total Static RAM memory (data + bss): 10680 bytes
//Total RAM memory (data + bss + heap + stack): 10680 bytes
//Total Flash memory (text + data + misc): 111099 bytes

// Online compiler:
// Code (Flash)	53.9 kB
// Code Data	5.1 kB
// RO Data (Flash)	3.6 kB
// RW Data (RAM)	0.4 kB
// ZI Data (RAM)	8.7 kB
// Debug			17.2 kB
// ROM				57.9 kB
// Flash			57.5 kB
// RAM				9.0 kB
// Info: Compile: armcc -c --gnu -O3 -Otime --split_sections --apcs=interwork --cpu=Cortex-M0 --md --no_depend_system_headers --c99 -D__ASSERT_MSG --cpp --no_rtti -DDEVICE_SPI=1 -DMBED_USERNAME=mjs7630 -D__MBED__=1 -DDEVICE_I2CSLAVE=1 -DTARGET_LIKE_MBED -DDEVICE_PORTINOUT=1 -D__MBED_CMSIS_RTOS_CM -DMBED_BUILD_TIMESTAMP=1518553844.05 -DDEVICE_LOWPOWERTIMER=1 -DDEVICE_RTC=1 -DTOOLCHAIN_object -DDEVICE_SERIAL_ASYNCH=1 -D__CMSIS_RTOS -DTARGET_STM32L0 -DTARGET_CORTEX_M -DTARGET_M0P -DDEVICE_ANALOGOUT=1 -DTARGET_UVISOR_UNSUPPORTED -DTARGET_NUCLEO_L073RZ -DDEVICE_INTERRUPTIN=1 -DTARGET_CORTEX -DDEVICE_I2C=1 -DDEVICE_PORTOUT=1 -D__CORTEX_M0PLUS -DDEVICE_STDIO_MESSAGES=1 -DDEVICE_SERIAL=1 -DTARGET_FF_MORPHO -DDEVICE_SPI_ASYNCH=1 -DTARGET_FF_ARDUINO -DTARGET_RELEASE -DTARGET_STM -DDEVICE_SERIAL_FC=1 -DTARGET_STM32L073xx -DDEVICE_TRNG=1 -DARM_MATH_CM0PLUS -DDEVICE_PORTIN=1 -DDEVICE_SLEEP=1 -DDEVICE_I2C_ASYNCH=1 -DTOOLCHAIN_ARM_STD -DDEVICE_SPISLAVE=1 -DDEVICE_ANALOGIN=1 -DDEVICE_PWMOUT=1 -DTARGET_STM32L073RZ -DTOOLCHAIN_ARM -DTARGET_LIKE_CORTEX_M0 -I/extras -I/extras/mbed-os.lib -I/extras/mbed-os.lib/cmsis -I/extras/mbed-os.lib/docs -I/extras/mbed-os.lib/drivers -I/extras/mbed-os.lib/events -I/extras/mbed-os.lib/events/equeue -I/extras/mbed-os.lib/features -I/extras/mbed-os.lib/features/frameworks -I/extras/mbed-os.lib/features/frameworks/greentea-client -I/extras/mbed-os.lib/features/frameworks/greentea-client/greentea-client -I/extras/mbed-os.lib/features/frameworks/greentea-client/source -I/extras/mbed-os.lib/features/frameworks/unity -I/extras/mbed-os.lib/features/frameworks/unity/source -I/extras/mbed-os.lib/features/frameworks/unity/unity -I/extras/mbed-os.lib/features/frameworks/utest -I/extras/mbed-os.lib/features/frameworks/utest/source -I/extras/mbed-os.lib/features/frameworks/utest/utest -I/extras/mbed-os.lib/features/mbedtls -I/extras/mbed-os.lib/features/mbedtls/importer -I/extras/mbed-os.lib/features/mbedtls/inc -I/extras/mbed-os.lib/features/mbedtls/inc/mbedtls -I/extras/mbed-os.lib/features/mbedtls/platform -I/extras/mbed-os.lib/features/mbedtls/platform/inc -I/extras/mbed-os.lib/features/mbedtls/platform/src -I/extras/mbed-os.lib/features/mbedtls/src -I/extras/mbed-os.lib/features/nanostack -I/extras/mbed-os.lib/features/netsocket -I/extras/mbed-os.lib/features/storage -I/extras/mbed-os.lib/hal -I/extras/mbed-os.lib/hal/storage_abstraction -I/extras/mbed-os.lib/platform -I/extras/mbed-os.lib/rtos -I/extras/mbed-os.lib/rtos/rtx -I/extras/mbed-os.lib/rtos/rtx/TARGET_CORTEX_M -I/extras/mbed-os.lib/rtos/rtx/TARGET_CORTEX_M/TARGET_M0P -I/extras/mbed-os.lib/rtos/rtx/TARGET_CORTEX_M/TARGET_M0P/TOOLCHAIN_ARM -I/extras/mbed-os.lib/targets -I/extras/mbed-os.lib/targets/TARGET_STM -I/extras/mbed-os.lib/targets/TARGET_STM/TARGET_STM32L0 -I/extras/mbed-os.lib/targets/TARGET_STM/TARGET_STM32L0/TARGET_NUCLEO_L073RZ -I/extras/mbed-os.lib/targets/TARGET_STM/TARGET_STM32L0/TARGET_NUCLEO_L073RZ/device -I/extras/mbed-os.lib/targets/TARGET_STM/TARGET_STM32L0/TARGET_NUCLEO_L073RZ/device/TOOLCHAIN_ARM_STD -I/extras/mbed-os.lib/targets/TARGET_STM/TARGET_STM32L0/device -I/src -I/source/esp8266-driver -I/source/esp8266-driver/ESP8266 -I/source/esp8266-driver/ESP8266/ATParser -I/source/esp8266-driver/ESP8266/ATParser/BufferedSerial -I/source/esp8266-driver/ESP8266/ATParser/BufferedSerial/Buffer --preinclude=/build/mbed_config.h --depend /build/esp8266-driver/ESP8266Interface.NUCLEO_L073RZ.d -o /build/esp8266-driver/ESP8266Interface.NUCLEO_L073RZ.o /source/esp8266-driver/ESP8266Interface.cpp in "esp8266-driver/ESP8266Interface.cpp", Line: 0, Col: 1

const char *sec2str(nsapi_security_t sec)
{
    switch (sec) {
        case NSAPI_SECURITY_NONE:
            return "None";
        case NSAPI_SECURITY_WEP:
            return "WEP";
        case NSAPI_SECURITY_WPA:
            return "WPA";
        case NSAPI_SECURITY_WPA2:
            return "WPA2";
        case NSAPI_SECURITY_WPA_WPA2:
            return "WPA/WPA2";
        case NSAPI_SECURITY_UNKNOWN:
        default:
            return "Unknown";
    }
}

void scan_demo(WiFiInterface *wifi)
{
    WiFiAccessPoint *ap;

    printf("Scan:\r\n");

    int count = wifi->scan(NULL,0);

    /* Limit number of network arbitrary to 15 */
    count = count < 15 ? count : 15;

    ap = new WiFiAccessPoint[count];
    count = wifi->scan(ap, count);
    for (int i = 0; i < count; i++)
    {
        printf("Network: %s secured: %s BSSID: %hhX:%hhX:%hhX:%hhx:%hhx:%hhx RSSI: %hhd Ch: %hhd\r\n", ap[i].get_ssid(),
               sec2str(ap[i].get_security()), ap[i].get_bssid()[0], ap[i].get_bssid()[1], ap[i].get_bssid()[2],
               ap[i].get_bssid()[3], ap[i].get_bssid()[4], ap[i].get_bssid()[5], ap[i].get_rssi(), ap[i].get_channel());
    }
    printf("%d networks available.\r\n", count);

    delete[] ap;
}

void http_demo(NetworkInterface *net)
{
    TCPSocket socket;

    printf("Sending HTTP request to www.arm.com...\r\n");

    // Open a socket on the network interface, and create a TCP connection to www.arm.com
    socket.open(net);
    socket.connect("www.arm.com", 80);

    // Send a simple http request
    char sbuffer[] = "GET / HTTP/1.1\r\nHost: www.arm.com\r\n\r\n";
    int scount = socket.send(sbuffer, sizeof sbuffer);
    printf("sent %d [%.*s]\r\n", scount, strstr(sbuffer, "\r\n")-sbuffer, sbuffer);

    // Recieve a simple http response and print out the response line
    char rbuffer[64];
    int rcount = socket.recv(rbuffer, sizeof rbuffer);
    printf("recv %d [%.*s]\r\n", rcount, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);

    // Close the socket to return its memory and bring down the network interface
    socket.close();
}

int main()
{
    printf("WiFi example\r\n\r\n");

    // Scan for available access points 
    scan_demo(&wifi);

    printf("\r\nConnecting...\r\n");
    int ret = wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\r\nConnection error\r\n");
        return -1;
    }

    printf("Success\r\n\r\n");
    printf("MAC: %s\r\n", wifi.get_mac_address());
    printf("IP: %s\r\n", wifi.get_ip_address());
    printf("Netmask: %s\r\n", wifi.get_netmask());
    printf("Gateway: %s\r\n", wifi.get_gateway());
    printf("RSSI: %d\r\n\r\n", wifi.get_rssi());

    http_demo(&wifi);

    wifi.disconnect();

    printf("\r\nDone\r\n");
}

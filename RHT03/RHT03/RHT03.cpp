/*
    RHT22.cpp - RHT22 sensor library
    Developed by HO WING KIT
    Modifications by Paul Adams
    More modifications by Tristan Hughes

    This library is free software; you can redistribute it and / or
    modify it under the terms of the GNU Leser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRENTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PATRICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA


    Humidity and Temperature Sensor RHT22 info found at
    http://www.sparkfun.com/products/10167
    same as RHT03 http://www.humiditycn.com    

    Version 0.1: 8-Jan-2011 by Ho Wing Kit
    Version 0.2: 29-Mar-2012 by Paul Adams
    
    Additional Credit: All the commenters on http://www.sparkfun.com/products/10167
    
*/

#include "RHT03.h"


// This should be 40, but the sensor is adding an extra bit at the start
#define RHT03_DATA_BIT_COUNT 41

RHT03::RHT03(PinName Data) {

    _data = Data;                // Set Data Pin
    _lastReadTime = time(NULL);
    _lastHumidity = 0;
    _lastTemperature = RHT03_ERROR_VALUE;
}

RHT03::~RHT03() {
}

RHT03_ERROR RHT03::readData() {
    int i, j, retryCount;
    int currentTemperature=0;
    int currentHumidity=0;
    unsigned int checkSum = 0, csPart1, csPart2, csPart3, csPart4;
    unsigned int bitTimes[RHT03_DATA_BIT_COUNT];
    RHT03_ERROR err = RHT_ERROR_NONE;
    time_t currentTime = time(NULL);

    DigitalInOut  DATA(_data);
       
    for (i = 0; i < RHT03_DATA_BIT_COUNT; i++) {
        bitTimes[i] = 0;
    }
    
   // if (int(currentTime - _lastReadTime) < 2) {        
   //     printf("RHT22 Error Access Time < 2s");
   //     err = RHT_ERROR_TOO_QUICK;
   // }   
    retryCount = 0;
    // Pin needs to start HIGH, wait unit it is HIGH with a timeout
    do {
        if (retryCount > 125) {
            //pc1.printf("RHT22 Bus busy!");
            err = RHT_BUS_HUNG;
            return err;
        }
        retryCount ++;
        wait_us(2);
    } while (DATA==0);   // exit on RHT22 return 'High' Signal within 250us
    
    // Send the activate pulse
    // Step 1: MCU send out start signal to RHT22 and RHT22 send
    //         response signal to MCU.
    // If always signal high-voltage-level, it means RHT22 is not 
    // working properly, please check the electrical connection status.
    //
    DATA.output(); // set pin to output data
    DATA = 0;      // MCU send out start signal to RHT22
    wait_ms(18);   // 18 ms wait (spec: at least 1ms)
    DATA = 1;      // MCU pull up 
    wait_us(40);
    DATA.input();  // set pin to receive data
    // Find the start of the ACK Pulse
    retryCount = 0;
    do {
        if (retryCount > 40)  { // (Spec is 20-40 us high)
            //pc1.printf("RHT22 not responding!");
            err = RHT_ERROR_NOT_PRESENT;
            return err;
        }
        retryCount++;
        wait_us(1);
    } while (DATA==1);   // Exit on RHT22 pull low within 40us
    if (err != RHT_ERROR_NONE) {
        // initialisation failed
        return err;    
    }
    wait_us(80); // RHT pull up ready to transmit data
    
    /*
    if (DATA == 0) {
        printf("RHT22 not ready!");
        err = RHT_ERROR_ACK_TOO_LONG;
        return err;
    }
    */
    
    // Reading the 5 byte data stream
    // Step 2: RHT22 send data to MCU
    //         Start bit -> low volage within 50us (actually could be anything from 35-75us)
    //         0         -> high volage within 26-28us (actually could be 10-40us)
    //         1         -> high volage within 70us (actually could be 60-85us)
    //         See http://www.sparkfun.com/products/10167#comment-4f118d6e757b7f536e000000
    
    
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 8; j++) {
            // Instead of relying on the data sheet, just wait while the RHT03 pin is low
            retryCount = 0;
            do {
                if (retryCount > 75)  {
                    //pc1.printf("RHT22 timeout waiting for data!");
                    err = RHT_ERROR_DATA_TIMEOUT;
                }
                retryCount++;
                wait_us(1);
            } while (DATA == 0);
            // We now wait for 40us
            wait_us(40);
            if (DATA == 1) {  
                // If pin is still high, bit value is a 1
                bitTimes[i*8+j] = 1;
            } else {  
                // The bit value is a 0
                bitTimes[i*8+j] = 0;
            }
            int count = 0;
            while (DATA == 1 && count < 100) {  
                wait_us(1); // Delay for 1 microsecond  
                count++;  
            }
        }
    }
    // Re-init RHT22 pin  
    DATA.output();  
    DATA = 1;

    // Now bitTimes have the actual bits
    // that were needed to find the end of each data bit
    // Note: the bits are offset by one from the data sheet, not sure why
    currentHumidity    = 0;
    currentTemperature = 0;
    checkSum           = 0;
    // First 16 bits is Humidity
    for (i=0; i<16; i++) {
        //printf("bit %d: %d  ", i, bitTimes[i+1]);
        if (bitTimes[i+1] > 0) {
            currentHumidity |= ( 1 << (15-i));
        }
    }
    
    // Second 16 bits is Temperature 
    for (i=0; i<16; i ++) {
        //printf("bit %d: %d  ", i+16, bitTimes[i+17]);
        if (bitTimes[i+17] > 0) {
            currentTemperature |= (1 <<(15-i));
        }
    }

    // Last 8 bit is Checksum
    for (i=0; i<8; i++) {
        //printf("bit %d: %d  ", i+32, bitTimes[i+33]);
        if (bitTimes[i+33] > 0) {
            checkSum |= (1 << (7-i));
        }
    }
   
    _lastHumidity = (float(currentHumidity) / 10.0);
    
    // if first bit of currentTemperature is 1, it is negative value.
    if ((currentTemperature & 0x8000)==0x8000) {        
        _lastTemperature = (float(currentTemperature & 0x7FFF) / 10.0) * -1.0;
    } else {
        _lastTemperature = float(currentTemperature) / 10.0;
    }

    // Calculate Check Sum
    csPart1 = currentHumidity >> 8;
    csPart2 = currentHumidity & 0xFF;
    csPart3 = currentTemperature >> 8;
    csPart4 = currentTemperature & 0xFF;
    if (checkSum == ((csPart1 + csPart2 + csPart3 + csPart4) & 0xFF)) {
        _lastReadTime = currentTime;
        //pc1.printf("OK-->Temperature:%f, Humidity:%f\r\n", _lastTemperature, _lastHumidity);
        err = RHT_ERROR_NONE;
    } else {
        //pc1.printf("RHT22 Checksum error!\n");
        //pc1.printf("Calculate check sum is %d\n",(csPart1 + csPart2 + csPart3 + csPart4) & 0xFF);
        //pc1.printf("Reading check sum is %d",checkSum);
        err = RHT_ERROR_CHECKSUM;
    }
    return err;
}

float RHT03::getTemperatureC() {
    return _lastTemperature;
}

float RHT03::getHumidity() {
    return _lastHumidity;
}
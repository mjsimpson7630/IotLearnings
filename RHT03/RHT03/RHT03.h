/* mbed RHT03 Library
  Copyright (c) 2011, sford, http://mbed.org
  Modifications by Tristan Hughes
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documnetation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to  whom the Software is
  furished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
 */

#ifndef MBED_RHT03_H
#define MBED_RHT03_H

#include "mbed.h"


#define RHT03_ERROR_VALUE -99.5

typedef enum {
    RHT_ERROR_NONE = 0,
    RHT_BUS_HUNG,
    RHT_ERROR_NOT_PRESENT,
    RHT_ERROR_ACK_TOO_LONG,
    RHT_ERROR_SYNC_TIMEOUT,
    RHT_ERROR_DATA_TIMEOUT,
    RHT_ERROR_CHECKSUM,
    RHT_ERROR_TOO_QUICK
} RHT03_ERROR;

/** RHT03 interface class for reading data from the sensor */
class RHT03
{
private:
    time_t  _lastReadTime;
    PinName _data;
    float   _lastHumidity;
    float   _lastTemperature;
public:
    /** Configure data pin
      * @param Data The data pin the RHT03 is attached to
      */
    RHT03(PinName Data);
    ~RHT03();
    /** Reads data from the RHT03
      * @return error type or successful read
      */
    RHT03_ERROR readData(void);
    /** Gives current humidity value
      * @return humidity value
      */
    float getHumidity();
    /** Gives current temperature value
      * @return temperature value
      */
    float getTemperatureC();
    void clockReset();
};

#endif /*_RHT03_H_*/

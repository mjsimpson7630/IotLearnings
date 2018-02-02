/*
 * (C) The University of Kent and Simon Cooksey 2015.
 */

#include "mbed.h"

#include "dht22.h"

Serial host(USBTX, USBRX);
DHT22 dht22(PTB18);


int main()
{
    DHT22_data_t dht22_data;
    while (true) {
        dht22.read(&dht22_data);
        
        float temperature = dht22_data.temp / 10.0f;
        float humidity = dht22_data.humidity / 10.0f;
        
        host.printf("Temperature: %2.2f    Humidity: %2.2f%%\r\n", temperature, humidity);
        wait_ms(500);
    }
}
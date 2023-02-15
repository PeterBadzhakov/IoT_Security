#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>

#include "bme.h" // Include custom header file

Adafruit_BME280 bme; // Use I2C interface
Adafruit_Sensor *bme_pressure = bme.getPressureSensor(); // Pointer to BME pressure sensor

void bme_init()
{
    Wire.begin(21, 22); // Initiate I2C with SDA and SCL pins
    bool status = bme.begin(0x76); // Begin BME280 sensor with I2C address 0x76
}

float bme_check()
{
    sensors_event_t pressure_event; // Event structure for BME pressure sensor
    bme_pressure->getEvent(&pressure_event); // Get the event for BME pressure sensor

    return pressure_event.pressure; // Return the pressure value
}

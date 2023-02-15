// Including header files for necessary classes
#include "pixelbar.h"
#include "bme.h"
#include "wifi_client.h"

// Setting values for WiFi network and TCP/IP communication
const char* ssid = "";
const char* password = "";
const char* ip = "";
uint16_t port = 8888;

// Creating a WifiClient object with given WiFi network and TCP/IP connection values
static WifiClient client(ssid, password, ip, port);

// Declaring a sensor data struct to store information from multiple sensor types
struct sensor_data
{
    enum SENSOR_TYPE : uint8_t
    {
        WIRE = 1
        //, LASER = 2
        //, CAMERA = 4
        , ALTITUDE = 8
    };

    uint8_t tripped = 0;
} sd;

void setup()
{
    // Delay to allow time for hardware to initialize
    delay(5000);
    // Start serial communication
    Serial.begin(115200);

    // Initialize BME280 sensor
    bme_init();

    // Set pin mode for pixel bar
    //pixelbar_init();
    pinMode(2, OUTPUT);
    
    // Connect to WiFi and send an initial message to the server
    client.connect();
    Serial.println(client.getIP());
    client.send("Alarm system online!\r\n", 16);
}

// Function to check sensor values and determine if any sensors have been triggered
uint8_t check_sensors()
{
    // Initialize sensor reading variables
    static float last_read = bme_check();
    float curr_read = bme_check();

    // Check for change in BME280 sensor reading
    if(abs(curr_read - last_read) > 0.10)
    {
        // Set the sensor tripped flag for altitude sensor
        sd.tripped |= sensor_data::SENSOR_TYPE::ALTITUDE;
    }
    last_read = curr_read;

    return sd.tripped;
}

void loop()
{
    // Check sensor values and set pixel bar state and alarm as needed
    if (check_sensors())
    {
        //pixelbar_on();
        digitalWrite(2, HIGH);
    }

    // Check for incoming TCP packets and delay before looping
    client.receive();
    delay(1000);

    // Print BME280 sensor value to serial monitor and delay before looping
    Serial.println(bme_check());
    delay(1000);
}

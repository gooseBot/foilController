#include <RH_ASK.h>   // Include the RH_ASK library
#include <SPI.h>      // Not actually used but needed to compile the RH_ASK library

const int txSpeed = 2000;
const int rxPin = 3;
const int txPin = 5;

RH_ASK radio(txSpeed, rxPin, txPin);
 
void setup()
{
    Serial.begin(9600);   // Use this for debugging
 
    if (!radio.init())
    {
         Serial.println("Radio module failed to initialize");
    }
}
 
void loop()
{
    // Create our message
    const char *msg = "Hello World";
 
    // Send our message
    radio.send((uint8_t*)msg, strlen(msg));
 
    // Wait until the data has been sent
    radio.waitPacketSent();
 
    // Delay since we dont want to send a trillion packets 
    delay(1000);
 
    // Also inform the serial port that we are done!
    Serial.println("Data Sent");
}

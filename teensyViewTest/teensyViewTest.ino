#include <TeensyView.h>  // Include the SFE_TeensyView library
#include <RH_ASK.h>   // Include the RH_ASK library
#include <SPI.h>      // Not actually used but needed to compile the RH_ASK library 

// Large font created following this. Cant make them more than 24bits in height.
// https://learn.sparkfun.com/tutorials/microview-hookup-guide/creating-fonts-for-microview

///////////////////////////////////
// TeensyView Object Declaration //
///////////////////////////////////
//Standard
#define PIN_RESET 15
#define PIN_DC    5
#define PIN_CS    10
#define PIN_SCK   13
#define PIN_MOSI  11
#define ASK_MAX_MESSAGE_LEN 5

TeensyView oled(PIN_RESET, PIN_DC, PIN_CS, PIN_SCK, PIN_MOSI);

// https://www.digikey.com/en/maker/blogs/2019/how-to-wirelessly-transmit-data-on-arduino
// http://www.airspayce.com/mikem/arduino/RadioHead/
// https://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html
RH_ASK radio(2000, 7);

void setup()
{
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.

  Serial.begin(9600);   // Use this for debugging
 
  if (!radio.init())
  {
    Serial.println("Radio module failed to initialize");
  }
}

void loop()
{

  uint8_t buf[ASK_MAX_MESSAGE_LEN] = {0};
  uint8_t buflen = sizeof(buf);
  if (radio.recv(buf, &buflen)) // if message received, save it
  {
    Serial.println((char*)buf); // print received message
  }
  
  oled.clear(PAGE);  // Clear the page
  oled.setFontType(1);  // Set font to custom font that overwrites largenumber font.
  oled.setCursor(0, 0); // move cursor
  oled.print((char*)buf);  // Write a byte out as a character
  oled.display();  // Send the PAGE to the OLED memory

  delay(200);
}

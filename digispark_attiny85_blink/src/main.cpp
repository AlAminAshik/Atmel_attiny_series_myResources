//This code shows how to upload simple blink code to digispark attiny85 board
//digispark board only stays at program mode for 5seconds after plugged in to computer
//so initiate upload process and the serial monitor will ask to plugin the device
//then insert the device and the code will be uploaded to the board
//if you program the board externally using arduino as ISP programmer, this method will not work anymore
//"upload_protocol = micronucleus" this line is added to initiate the upload process in platformio.ini file

#include <Arduino.h>
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(200);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(200);                      // wait for a second
}

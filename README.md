# The Atmel Attiny series
* Contains several codes and resources regarding how to program, code, optimize this MCU

## *digispark_attiny85_blink
* *This code shows how to upload simple blink code to digispark attiny85 board
* digispark board only stays at program mode for 5seconds after plugged in to computer
* so initiate upload process and the serial monitor will ask to plugin the device
* then insert the device and the code will be uploaded to the board
* if you program the board externally using arduino as ISP programmer, this method will not work anymore
* "upload_protocol = micronucleus" this line is added to initiate the upload process in platformio.ini file

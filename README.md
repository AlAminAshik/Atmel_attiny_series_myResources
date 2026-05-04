# The Atmel Attiny series
* Contains several codes and resources regarding how to program, code, optimize this MCU

## *digispark_attiny85_blink
* *This code shows how to upload simple blink code to digispark attiny85 board
* digispark board only stays at program mode for 5seconds after plugged in to computer
* so initiate upload process and the serial monitor will ask to plugin the device
* then insert the device and the code will be uploaded to the board
* if you program the board externally using arduino as ISP programmer, this method will not work anymore
* "upload_protocol = micronucleus" this line is added to initiate the upload process in platformio.ini file

## * Uploading code to attiny1614
For uploading code to attiny1614 using usb to ttl converter.

Fuses of attiny1614:
     --fuses
    "2:0x06 6:0x12 8:0x00"

### fuse 8 is default set at 0x00, keep it as it is
### fuse 2
* 0x02 means very short startup delay, implies internal oscillator is used
* 0x06 means longer startup delay
### fuse 6
* 0x04 means BOD enabled at 2.6V threshold and sampled mode (problem can arise)
* 0x02 means BOD enabled at 2.6V threshold and continous mode (better for 3.3V system)
* 0x12 means BOD enabled at 4.2V threshold and continous mode (better for 5V stable system)

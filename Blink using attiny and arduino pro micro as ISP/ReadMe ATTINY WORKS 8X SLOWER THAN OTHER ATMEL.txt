|||| When working with attiny, you must understand the attiny works 8x slower by default. which means delay(1000) will work as if its delay(8000)!
> This is problematic when working with IR receivers or sonar sensors since timing is crucial.

||||Why this happens: (this is for attiny13, but others should be similar)
> By default, the ATtiny13A has the CKDIV8 fuse enabled, which divides the clock by 8.
> The internal RC oscillator runs at 9.6 MHz, so with the divide-by-8 prescaler, the actual clock speed is: 1.2MHz
> However, if the chip is instead running at 1.2 MHz and the compiler assumes it is running at 9.6 MHz, delays will be 8 times slower.
> The clock speed is divided by 8 in default chips to save power and stability.

||||How to solve this:
||||METHOD 1: USING AVRDUDE (DIFFCULT)
> We need to change the fuse settings and disable the CKDIV8 fuse. this will make the chip run at 9.6MHz directly. (e.g. for attiny13)
> Use AVRdude to set the fuse.
> To download AVRdude download the .exe file from https://github.com/avrdudes/avrdude/releases. Download the windows-x64.zip
> In the downloads folder extract the downloaded file and run cmd inside the folder.
> type avrdude --v and it will print the version number.
>> Before changing fuse, prepare an Arduino (e.g. uno) as ISP and connect the wires of uno with attiny in programming configuration. ((REMEMBER to add a 10uF capacitor between arduino's reset and GND to prevent unexpected resets).
> Back to cmd prompt; 
Type FOR ATTINY13A: "avrdude -c arduino -p t13 -P COMXX -b 19200 -U lfuse:w:0x7A:m"
Type FOR ATTINY85 : "avrdude -c arduino -p t85 -P COMxx -b 19200 -B 125 -U lfuse:w:0xE2:m"
Change the COMXX port with the designated port. (can be found in Arduno IDE port settings)
> It should return success!

||||METHOD 2: USING ARDUINO IDE (EASY)
>> We need to override the clock source, this will disable the CKDIV8 fuse and let the chip run directly at 8MHz. (e.g. for attiny85)
> This can be done by burning bootloader from Arduino IDE.
> Install the board on Arduino IDE. Inside the additional boards manager, add this URL:
https://raw.githubusercontent.com/sleemanj/optiboot/master/dists/package_gogo_diy_attiny_index.json
> Then download DIY attiny by James sleman from boards manager.
>> Before changing fuse, prepare an Arduino (e.g. uno) as ISP and connect the wires of uno with attiny in programming configuration. ((REMEMBER to add a 10uF capacitor between arduino's reset and GND to prevent unexpected resets).
> Set the board, tools > boards > DIYAttiny > AttinyXX.
> Go to tools > override clock source > (e.g. Internal oscillator 8MHz).
> Make sure tools > programmer is selected as Arduino as ISP.
> Then burn the bootloader tools > burn bootloader.
> It should burn successfully!

||||Test:
> Upload the blink code to attiny using previous connection (Arduino ISP).
> use delay(1000);
> The light should blink every 1 seconds.
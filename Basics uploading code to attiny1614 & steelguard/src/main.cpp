#include <Arduino.h>
#include <avr/io.h>

char inputBuffer[7]; // Buffer to store incoming serial data
byte index = 0; // Index for inputBuffer

#define sirenLight PIN_A3      //pin where red light and buzzer are connected 
#define yellowLight PIN_A2    //pin where yellow light is connected
#define greenLight PIN_A1     //pin where green light is connected
#define triggerIn PIN_PB0      // GPIO pin for cutting trigger input circuit
#define alarmIn PIN_PB1        // GPIO pin for alarm button input circuit

uint8_t sirenLightState = 0;
uint8_t yellowLightState = 0;
uint8_t greenLightState = 0;
bool triggerInputState = false;
bool alarmInputState = false;
bool sirenActive = false;

void blinkSiren() {
    static unsigned long lastToggle = 0;
    unsigned long now = millis();

    if (now - lastToggle >= 500) {  // toggle every 500ms = 1Hz blink
        lastToggle = now;
        digitalWrite(sirenLight, sirenActive ? LOW : HIGH); // Toggle siren light
        sirenActive = !sirenActive; // Update siren active state
    }
}

void setup() {
    Serial.begin(4800);
    pinMode(sirenLight , OUTPUT);
    pinMode(yellowLight , OUTPUT);
    pinMode(greenLight , OUTPUT);
    pinMode(triggerIn , INPUT_PULLUP);
    pinMode(alarmIn , INPUT_PULLUP);
}


void loop() {
    // Read serial input and update light states
    while (Serial.available()){
        char c = Serial.read();
        if (c == '\n') { // End of command
        //inputBuffer.trim(); // Remove any whitespace
        inputBuffer[index] = '\0'; // Null-terminate the string
            if (index >= 6){
                //format i.e. R1Y0G1
                sirenLightState = inputBuffer[1] - '0';  // Convert char to int
                yellowLightState = inputBuffer[3] - '0';  // Convert char to int
                greenLightState = inputBuffer[5] - '0';  // Convert char to int
            }
        index = 0; //clear buffer for next command
        }
        else {    //keep reading characters until newline is received, and store them in inputBuffer
            if (index < sizeof(inputBuffer) - 1) { // Ensure we don't overflow the buffer
                inputBuffer[index++] = c; // Add character to buffer and increment index
            }
        }
    }


    //Toggle lights based on received command
    // Blink siren light if it's on
    if (sirenLightState) {
        blinkSiren();
    } else {
        digitalWrite(sirenLight, LOW); // Ensure siren light is off if state is 0
    }
    digitalWrite(yellowLight, yellowLightState ? HIGH : LOW);
    digitalWrite(greenLight, greenLightState ? HIGH : LOW);

    // Read trigger and alarm input states
    triggerInputState = digitalRead(triggerIn);
    alarmInputState = digitalRead(alarmIn);
    Serial.print("R"+String(sirenLightState)+"Y"+String(yellowLightState)+"G"+String(greenLightState)+"T"+String(triggerInputState)+"A"+String(alarmInputState)+"\n");
    delay(20);
}
/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */
#include <M5StickCPlus.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 9;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
//Pause LGTV
uint16_t rawData[68] = {9000,4350,600,500,600,500,600,1600,600,500,600,500,600,500,600,500,600,550,550,1650,550,1650,600,500,600,1600,600,1600,600,1600,600,1600,600,1600,600,500,600,1600,600,500,600,1600,600,1600,600,1600,600,500,600,1600,600,1600,600,500,600,1600,600,500,600,500,600,550,550,1650,550,550,550,};
// Example Samsung A/C state captured from IRrecvDumpV2.ino

//Play LGTV
uint16_t nawData[68] = {8950,4400,600,500,600,500,600,1600,600,500,600,500,600,500,600,500,600,500,600,1600,600,1600,600,500,600,1600,600,1600,600,1600,600,1600,600,1600,600,500,600,550,550,550,550,550,550,1650,550,1650,550,550,550,1650,550,1650,550,1650,550,1650,550,1650,550,550,550,550,550,1650,550,550,600,};
// PLAY [68] = {8950,4400,600,500,600,500,600,1600,600,500,600,500,600,500,600,500,600,500,600,1600,600,1600,600,500,600,1600,600,1600,600,1600,600,1600,600,1600,600,500,600,550,550,550,550,550,550,1650,550,1650,550,550,550,1650,550,1650,550,1650,550,1650,550,1650,550,550,550,550,550,1650,550,550,600,};

uint8_t samsungState[kSamsungAcStateLength] = {
    0x02, 0x92, 0x0F, 0x00, 0x00, 0x00, 0xF0,
    0x01, 0xE2, 0xFE, 0x71, 0x40, 0x11, 0xF0};

void setup() {
  M5.begin();
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

// ammended while loop to allow for if conditions to be followed - and it works :) 
void loop() {
  while(true) {
    if(digitalRead(M5_BUTTON_HOME) == LOW) {
      Serial.println("PAUSE ^^");
      M5.lcd.println("PAUSE ^^");
      irsend.sendRaw(rawData, 68, 38);  // Send a raw data capture at 38kHz.
      Serial.println("a Samsung A/C state from IRrecvDumpV2");
      irsend.sendSamsungAC(samsungState);
      delay(200);
    }
    if (digitalRead(M5_BUTTON_RST) == LOW) {
      Serial.println("PLAY ^^");
      M5.lcd.println("PLAY ^^");
      irsend.sendRaw(nawData, 68, 38);  // Send a raw data capture at 38kHz.
      Serial.println("a Samsung A/C state from IRrecvDumpV2");
      irsend.sendSamsungAC(samsungState);
      delay(200);
    }
  }
}

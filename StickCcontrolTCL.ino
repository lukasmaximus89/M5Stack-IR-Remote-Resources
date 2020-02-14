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

#include <M5StickC.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 9;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Vol up
uint16_t rawData[155] = {4022, 3940,  546, 1940,  572, 1916,  572, 1918,  570, 1918,  570, 928,  570, 928,  544, 1942,  570, 928,  570, 1918,  568, 1918,  560, 1930,  570, 1918,  570, 928,  570, 928,  570, 926,  570, 928,  570, 1916,  570, 1918,  570, 928,  570, 1918,  570, 928,  570, 928,  570, 928,  570, 928,  570, 8388,  4046, 3914,  572, 1916,  570, 1918,  572, 1918,  570, 1916,  572, 928,  570, 928,  570, 1918,  570, 928,  568, 1918,  572, 1918,  570, 1918,  570, 1918,  570, 928,  570, 928,  568, 928,  568, 930,  568, 1920,  568, 1920,  568, 930,  542, 1946,  566, 932,  542, 956,  542, 958,  542, 954,  542, 8416,  3964, 3996,  542, 1944,  540, 1948,  538, 1950,  540, 1948,  542, 956,  488, 1010,  488, 2000,  488, 1010,  488, 2000,  488, 2000,  488, 2000,  488, 2000,  488, 1010,  488, 1010,  488, 1010,  488, 1010,  488, 2000,  488, 2000,  488, 1010,  488, 2000,  488, 1010,  488, 1010,  488, 1008,  488, 1010,  488};  // NIKAI D0F2F

uint16_t nawData[103] = {4022, 3940,  544, 1942,  544, 1946,  542, 1944,  544, 1944,  544, 954,  544, 954,  542, 1942,  544, 954,  544, 1944,  544, 1944,  544, 1944,  544, 954,  544, 954,  544, 952,  546, 952,  544, 954,  544, 1944,  544, 1944,  544, 954,  544, 1942,  546, 954,  542, 954,  544, 954,  544, 1944,  544, 8416,  4020, 3940,  544, 1968,  520, 1944,  544, 1944,  544, 1944,  544, 954,  544, 978,  520, 1946,  542, 954,  546, 1942,  544, 1944,  544, 1944,  544, 952,  572, 926,  544, 954,  544, 954,  542, 978,  520, 1944,  544, 1946,  542, 954,  570, 1918,  544, 954,  544, 954,  544, 954,  544, 1944,  544};  // NIKAI D1F2E




void setup() {
  M5.begin();
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

void loop() {
  if(digitalRead(M5_BUTTON_HOME) == LOW){
  Serial.println("Power On");
  M5.Lcd.println("Power On");
  irsend.sendRaw(rawData, 155, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
  }
  else if(digitalRead(M5_BUTTON_RST) == LOW){
  Serial.println("Channel");
  M5.Lcd.println("Channel");
  irsend.sendRaw(nawData, 103, 38);  // Send a raw data capture at 38kHz.
  delay(2000); 
  }
 // else(){
//  M5.Lcd.clear();
 // }
}

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 12;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
const int btnpin = 39;
int buttonState = 0;

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Power On
uint16_t rawData[11] = {1078, 154,  96, 180,  198, 28094,  320, 1694,  346, 3610,  320};

void setup() {
  pinMode(btnpin, INPUT);
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

void loop() {
  buttonState = digitalRead(btnpin);
  if (buttonState == LOW){
      Serial.println("Power On");
      irsend.sendRaw(rawData, 11, 38);  // Send a raw data capture at 38kHz.
      delay(2000);
     }
}

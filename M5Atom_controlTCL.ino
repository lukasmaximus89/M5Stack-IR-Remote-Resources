#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 12;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
const int btnpin = 39;
int buttonState = 0;

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Power On
uint16_t rawData[155] = {4066, 3918,  570, 1918,  572, 1918,  570, 1920,  570, 1920,  570, 928,  570, 1920,  568, 930,  570, 1918,  572, 928,  568, 1920,  570, 1918,  546, 1946,  570, 928,  570, 928,  570, 928,  570, 928,  570, 1918,  570, 930,  544, 1944,  572, 928,  544, 1944,  572, 926,  548, 952,  570, 928,  570, 8394,  4050, 3916,  570, 1918,  546, 1944,  570, 1920,  570, 1918,  572, 928,  544, 1946,  570, 928,  570, 1898,  590, 930,  570, 1918,  570, 1918,  570, 1920,  570, 928,  570, 930,  568, 928,  570, 928,  570, 1922,  568, 930,  570, 1920,  570, 928,  570, 1920,  570, 930,  570, 928,  570, 930,  570, 8376,  4068, 3918,  570, 1900,  564, 1944,  570, 1918,  572, 1900,  588, 910,  590, 1920,  570, 930,  570, 1918,  570, 930,  570, 1918,  570, 1918,  548, 1944,  572, 908,  590, 930,  570, 908,  564, 956,  568, 1920,  570, 930,  570, 1918,  572, 928,  570, 1918,  546, 954,  570, 908,  590, 930,  544};  // NIKAI A8F57

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
      irsend.sendRaw(rawData, 155, 38);  // Send a raw data capture at 38kHz.
      delay(2000);
     }
}

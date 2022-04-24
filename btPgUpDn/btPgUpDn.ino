/* Bluetooth page turning pedal for ESP32
 *  Francis Deck
 *  
 *  Also tested on this hardware: WEMOS Lite V1.0.0
 *  https://www.aliexpress.com/item/33009178296.html
 *  Arduino setup:
 *  Board: WEMOS LOLIN32
 *  Upload speed: 115200
 *  CPU frequency: 240 MHz
 *  Flash frequency: 80 MHz
 *  Partition scheme: Default
 *  
 *  Tested on hardware: SparkFun ESP32 Thing
 *  Schematic: https://cdn.sparkfun.com/assets/learn_tutorials/5/0/7/esp32-thing-schematic.pdf
 *  Board mod: Cut jumper SJ1, added 5.1k resistor to reduce charging current for
 *  300 mAh LiPo battery. At the higher current, the battery was heating up
 *  
 *  Starting point was the example program for this library:
 *  https://github.com/T-vK/ESP32-BLE-Keyboard
 *  You need to visit this repository, download it library as a ZIP file
 *  and install it using the library manager. This is done with:
 *    Sketch --> Include Library --> Add ZIP library
*/

// Pin definitions

//#define esp32Thing
#define wemos
// for WEMOS board, compile under WEMOS LOLIN32 Lite
// add to external libraries: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
// add "esp32" in library manager

#define pgUp 17 // Page-Up button, SPST momentary contact switch closure to ground
#define pgDn 16 // Page-Down buttton, SPST momentary contact switch closure to ground
#define esc 4 // Escape button, multiple uses
#ifdef esp32Thing
  #define ledPin 5 // On-board LED indicator
  #define ePin 0 // On-board pushbutton
#endif
#ifdef wemos
  #define ledPin 22
  #define LED_ON LOW
  #define LED_OFF HIGH
#endif

#include <BleKeyboard.h>
// Download BleKeyboard from here: https://github.com/T-vK/ESP32-BLE-Keyboard

BleKeyboard bleKeyboard("PtPedal");

void setup() {
  pinMode(pgUp, INPUT_PULLUP);
  pinMode(pgDn, INPUT_PULLUP);
  pinMode(esc, INPUT_PULLUP);
  #ifdef esp32Thing
    pinMode(ePin, INPUT_PULLUP);
  #endif
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LED_OFF);
  // holding escape button during power-up suppresses Bluetooth, for charging
  if (!digitalRead(esc)){
    while(1);
  }
  bleKeyboard.begin();
}

void processKey(int pin, uint8_t key){
  if (!digitalRead(pin)) {
      digitalWrite(ledPin, LED_ON);
      delay(100);
      bleKeyboard.write(key);
      bleKeyboard.releaseAll();
      while(!digitalRead(pin));
      delay(100);
      digitalWrite(ledPin, LED_OFF);
    }
}
void loop() {

  // Each key is de-bounced in a primitive way, sends one character to the
  // host, and then waits for the key to be released. There is no auto-repeat,
  // because that's a bad thing in a sheet music reading situation
  
  while(bleKeyboard.isConnected()) {
    digitalWrite(ledPin, LED_OFF);
    processKey(pgUp, KEY_PAGE_UP);
    processKey(pgDn, KEY_PAGE_DOWN);
    processKey(esc, KEY_F5); // F5 toggles presentation mode in Sumatra PDF.
    
    #ifdef esp32Thing
      if (!digitalRead(ePin)) {
        digitalWrite(ledPin, LED_ON);
        delay(100);
        bleKeyboard.print("e");
        while(!digitalRead(pgDn));
        delay(100);
        digitalWrite(ledPin, LED_OFF);
      }
    #endif
  }

  // So long as the program is waiting for a connection from the host, it blinks
  // the LED.

  digitalWrite(ledPin, (millis()/128) % 2);
}

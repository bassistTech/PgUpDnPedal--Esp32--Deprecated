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

#define esp32Thing
//#define wemos

#define pgUp 17 // Page-Up button, SPST momentary contact switch closure to ground
#define pgDn 16 // Page-Down buttton, SPST momentary contact switch closure to ground
#ifdef esp32Thing
  #define ledPin 5 // On-board LED indicator
  #define ePin 0 // On-board pushbutton
#endif
#ifdef wemos
  #define ledPin 22
#endif

#include <BleKeyboard.h>

BleKeyboard bleKeyboard("PtPedal");

void setup() {
  pinMode(pgUp, INPUT_PULLUP);
  pinMode(pgDn, INPUT_PULLUP);
  #ifdef esp32Thing
    pinMode(ePin, INPUT_PULLUP);
  #endif
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  bleKeyboard.begin();
}

void loop() {
  int pu, pd;
  int i;

  // Each key is de-bounced in a primitive way, sends one character to the
  // host, and then waits for the key to be released. There is no auto-repeat,
  // because that's a bad thing in a sheet music reading situation
  
  while(bleKeyboard.isConnected()) {
    digitalWrite(ledPin, HIGH);
    
    if (!digitalRead(pgUp)) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      bleKeyboard.write(KEY_PAGE_UP);
      bleKeyboard.releaseAll();
      while(!digitalRead(pgUp));
      delay(100);
      digitalWrite(ledPin, LOW);
    }
    
    if (!digitalRead(pgDn)) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      bleKeyboard.write(KEY_PAGE_DOWN);
      bleKeyboard.releaseAll();
      while(!digitalRead(pgDn));
      delay(100);
      digitalWrite(ledPin, LOW);
    }

    #ifdef esp32Thing
      if (!digitalRead(ePin)) {
        digitalWrite(ledPin, HIGH);
        delay(100);
        bleKeyboard.print("e");
        while(!digitalRead(pgDn));
        delay(100);
        digitalWrite(ledPin, LOW);
      }
    #endif
  }

  // So long as the program is waiting for a connection from the host, it blinks
  // the LED.

  digitalWrite(ledPin, (millis()/128) % 2);
}

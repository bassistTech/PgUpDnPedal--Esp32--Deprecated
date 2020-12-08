/* PgUpDn, a page turning pedal for Teensy LC  

MIT License

Copyright (c) 2020 Francis Deck

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(13, OUTPUT); // this is the on board LED
  digitalWrite(13, LOW);
}

// globals for the status of the two buttons

int b0 = 0;
int b1 = 0; 

void checkbuttons(){
  // check the status of the buttons with very simple de-bounce
  // we simply check 10 times with 1 ms delay in between, and
  // the button is said to be pressed if it agrees on all
  // 10 tries.
  int i, c0 = 0, c1 = 0;
  for (i=0; i<10; i++) {
    if (!digitalRead(0)) c0++;
    if (!digitalRead(1)) c1++;
    delay(1);
  }
  b0 = c0 == 10;
  b1 = c1 == 10;
}

void loop() {
  checkbuttons();
  if (b0) {
    Keyboard.press(KEY_PAGE_UP);
    Keyboard.release(KEY_PAGE_UP);
    digitalWrite(13, HIGH);
    delay(100);
    while (b0) checkbuttons(); // wait for release
   
  }
  if (b1) {
    Keyboard.press(KEY_PAGE_DOWN);
    Keyboard.release(KEY_PAGE_DOWN);
    digitalWrite(13,  HIGH);
    delay(100);
    while (b1) checkbuttons(); // wait for release
  }
  digitalWrite(13, LOW);
}

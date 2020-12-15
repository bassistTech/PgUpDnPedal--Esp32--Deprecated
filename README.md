# PgUpDnPedal
## Page turning pedal

Francis Deck, Dec. 7, 2020

This is a simple design for a page turning pedal. Its most likely use is reading sheet music on a tablet device.

**Audience**: For now, fairly advanced hobbyists who are comfortable with basic circuit construction such as soldering, and working with the Arduino development environment. *While unlikely, it is possible to damage your personal computer with homemade hardware plugged into it, under severe conditions.*

**Motivation**: I wanted to try reading music from a tablet, just to see if I can stand the tiny screen. I'm a jazz double bassist, so my hands are occupied when I'm playing, and while it's easy to flip pages on paper charts, it can be frustrating on a tablet. You can buy a Bluetooth pedal for this purpose, but I decided to quickly whip one up of my own.

For non-musicians, "reading" in this context means *playing* music directly from a written source. 

**Design platform**: It's based on Teensy LC, a low cost microcontroller development board. For hardware, all it needs are two pushbutton switches and a housing. The Teensy LC is intended to be programmed in the Arduino development environment, and it comes with libraries for emulating a USB keyboard. So the pedal is just a two button keyboard!

I really like the Teensy family of boards. Even the cheapest Teensy has a much more powerful processor than the original Arduino, and their latest version is the most powerful microconroller development board available right now. You can treat a Teensy board "like an Arduino" using the standard libraries, and a lot of Arduino code will run on directly. This lets you tap into copious code that hobbyists have shared online. But Arduino is also just a thin wrapper around GCC, and the Teensy libraries expose the entire register space of the microcontrollers, so it's easy to reach bare metal and make use of the full functionality of the chips at top performance.

'''https://www.pjrc.com/teensy/teensyLC.html'''

In reality, the Teensy LC, for 12 bucks, is overkill. A 32-bit, 48 MHz MCU to emulate a two button keyboard? But I use Teensy's for other purposes, so if this thing proves to be useless, I'll use the Teensy for something else.

**Design process**: I started by hooking up the switches and confirming that they physically work. The circuit uses the built-in "pull up" function of the microcontroller, which passes a small amount of current to the switch through a resistor. With the switch open, the pin reads as "high," and when connected to ground, reads as "low." Thus, a "low" state means the button is being pushed. A couple of issues need to be resolved:

1. "Contact bounce" happens when the switch first makes contact, and may turn itself on and off a few times before it settles into a stable position. This could be mis-interpreted as multiple button presses, sending me off to some random page. I wrote a simple "de-bouncing" algorithm that just reads the switch 10 times with a bit of delay in between, and confirms that it's in the same state.

2. What happens when I don't release a switch? My feet are clumsy and I'm thinking about the music. I want one button push to flip one page. I deliberately don't want the buttons to repeat, because there's seldom a use for flipping quickly through a chart, and turning past a page is an easy to way to get lost in a complex arrangement. It works in a way that overrides the built-in keyboard repetition of Windows.

## Circuit design

Here it is, in all its glory: A Teensy LC and two pushbutton switches. The numbers 0 and 1 refer to the numbers silk-screened onto the bottom of the Teensy LC board. G is ground. The switches are plain momentary contact pushbutton switches.

![Schematic](./img/schem.png)

And here's the build. I made the enclosure out of wood and a piece of Lexan from my scrap bin.

![Picture](./img/picture.png)

## Program code

The Arduino code is in the PgUpDn folder. To use it, you need to install the latest version of Arduino on your PC, as well as the Teensyduino package from PJRC. As a note to the un-initiated, Arduino is considered to be "easy" for enthusiasts, but if you're a complete beginner at this stuff, there's actually a fairly steep learning curve.

When you get Arduino and Teensyduino installed, you can open the source code file, and you'll need to choose some settings:

  Tools --> Board --> Teensyduino --> Teensy LC
  
  USB Type --> Keyboard
  
The first setting tells it you've got a Teensy LC, among the many possible Teensy boards. The second tells it to add USB keyboard emulation firmware to the libraries that are available to your program.

I will add some more detailed instructions on where to find the tools that you need, but for now, this is it.
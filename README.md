# PgUpDnPedal
## Page turning pedal based on ESP32 microcontroller

Francis Deck, Dec. 7, 2020

### Purpose

Bluetooth enabled page turning pedal, for reading sheet music on a tablet device.

### Status of project

It works, but the project has turned into an adventure in low cost sourcing. I've provided two bills of materials (BOMs) because the cheap BOM involves stuff that's probably fake. The fake-ness may involve problems with management of the LiPo battery.

### Audience

For now, fairly advanced hobbyists who are comfortable with basic circuit construction such as soldering, and working with the Arduino development environment, plus use of test equipment such as a voltmeter. If you're just looking for a way to avoid paying the full cost of a commercial page turning pedal, this is probably not a good project for you.

### Motivation

I wanted to try reading music from a tablet, just to see if I can stand the tiny screen. I'm a jazz double bassist, so my hands are occupied when I'm playing, and while it's easy to flip pages on paper charts, it can be frustrating on a tablet. You can buy a Bluetooth pedal for this purpose, but I decided to quickly whip one up of my own.

For non-musicians, "reading" in this context means *sight-reading* which is the specialized art of *playing* music directly from a written source. Many musicians, for instance in folk or rock music, or the production of electronic music, will never need to sight-read.

## Design information

### Design platform

**Expensive BOM**: SparkFun "ESP32 Thing" microcontroller board

**Cheap BOM**: Possibly third party version of Wemos LOLIN32 Lite board, oops.

Almost every hobbyist design involving any kind of radio communications (Bluetooth, WiFi, etc.) uses the same platform: The Espressif ESP32 microcontroller (MCU) chip. This is a 32 bit MCU with built-in wireless capability, and generous support through libraries that can be used within the Arduino development environment.

Thanks to Arduino, both hardware designs can use the same source code. 

*Note to casual readers*: I plan to write a bit about MCU's, what they are, and why they're such a huge thing for contemporary electronics design, stay tuned.

## Circuit design

Here it is, in all its glory

![Schematic](./img/schem.png)

Here's a top view of the build. I made the enclosure out of wood and a piece of Lexan from my scrap bin.

![Picture](./img/picture.png)

... and here's a bottom view.

Pins 16 and 17 of the MCU board will both be configured by the program to have pull-up resistors, meaning that they will present themselves as logic HIGH when nobody's stepping on them.

Since the board is designed to have a battery plug directly into it, there's no way to turn it off unless you cut a wire to insert a switch, which I've done. As a precaution, make sure the switch is turned off when soldering the battery connections. Also, *don't cut off both wires at once, that will short the leads together and damage the batttery!*

That's it. The MCU is doing most of the work! For this reason, I'll discuss some of the interesting features of the program, in the next section.

## Program code

The program has just a few basic parts, because it's so simple. There's an initialization that attempts to start the Bluetooth connection while flashing the LED. The LED will turn off when the connection with your tablet device is successful.

There's a loop that checks for closures of the buttons. Almost any mechanical switch has a behavior called "bounce," where it will make and break its connection a few times before settling down. I don't want my program to count multiple closures each time I step on a button, so I need a "de-bounce" algorithm:

My program behaves differently than a real keyboard. Most keyboards have an auto-repeat feature, but I absolutely don't want that. I want exactly one page per button press, even if I don't take my foot off the pedal right away. So my program waits for each button to be released before going back into the main loop.

## Bill of materials

This is where it gets weird. I built my first prototype from spare parts, so I wasn't concerned about the cost. For the MCU, I chose a SparkFun ESP32 Thing board:

https://www.sparkfun.com/products/13907

I still recommend it. But I was fascinated with the idea of trying to do this with really cheap parts, so I sourced an alternative BOM from AliExpress. This included a "WEMOS Lite V1.0.0" board. The parts arrived, I built my prototype, and it worked fine. But I was interested in knowing a bit more about the board, so I went looking for a schematic, and discovered this video.

https://www.youtube.com/watch?v=a9f9vHjQSfQ

According to the video, the original WEMOS LOLIN32 Lite board was discontinued, and my board resembled the one identified as a replacement in this video. *I can't pass judgment on this, since I really don't know the details.* Also, my board works just fine. So I'm chalking it up to being a puzzle, but meanwhile, another board, the LOLIN D32, looks like it might be preferable:

https://www.aliexpress.com/item/32808551116.html

The moral of my story for now is that *there is some value to sourcing parts from reputable makers and distributors.* Places like Mouser Electronics add value, which is why I use them for my business while paying a bit more for parts. There's definitely a "wild west" vibe to global electronics sourcing these days.

| Part | Mouser | AliExpress alternative BOM |
| ---- | ------ | ---------- |
| Microcontroller board | 474-DEV-13907 | https://www.aliexpress.com/item/33009178296.html |
| Pushbutton switches (x2) | 633-SB4011NCH  | https://www.aliexpress.com/item/33014143212.html |
| Rocker switch | 612-3112BBLKBLKRDNEF | https://www.aliexpress.com/item/4000899454626.html |
| LiPo battery | 406-ASR00007 | https://www.aliexpress.com/item/4000827234167.html |
| 10k resistor | | |

For many of these parts, you can choose your own favorites. Choose based on what tools you have at your disposal. I have a "uni bit" stepped drill bit that works great in sheet material, so I choose switches that go into round holes. And I looked for parts that were at the cheaper end of the price scale.
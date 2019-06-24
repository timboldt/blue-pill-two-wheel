## SSD1306 OLED Display

### Overview

* 0.96" (25mm) monochrome OLED display.
* I2C interface. (They also come in SPI versions, etc.)
* SSD1306 display controller ([datasheeet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)).
* 128 pixels wide and 64 pixels high. (They also come in other sizes.)
* Although it is monochrome, the top 16 rows are often a different color from the bottom 48 rows, e.g. yellow on top and blue on the bottom.
* [Example device](https://www.uctronics.com/download/Amazon/U602602.pdf).
* The power on sequence is fairly complex and requires about 15 control messages.
* It has a number of different ways to organize the memory, but for our purposes, the bytes are oriented vertically with the least significant bits at the top.
* Example: writing [0x0C, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0x0C] into the first 8 bytes will draw a heart like this:
    ```
    --------
    -XX--XX-
    XXXXXXXX
    XXXXXXXX
    -XXXXXX-
    --XXXX--
    ---XX---
    --------
    ```

### Driver

There are plenty of drivers out there, but what fun is that? My goal with this project was to display two types of information: text and strip chart plots.

#### Text Display

Text is drawn by sending 8 bytes for each character to draw an 8x8 figure. This makes for (up to) 8 lines of text, with 16 characters on each line. Each line is treated as an independently addressable block of text, with no line wrapping, line feeds, or carraige returns.

This process is quite efficient because we can take advantage of the fact that the SSD1306 will auto-advance the target memory location after each byte is written.

#### Chart Display

The strip chart is a 32-pixel (4 byte) high graph. The graph auto-advances one pixel to the right after each value is written. When it reaches the right-hand side, it restarts at column 0.
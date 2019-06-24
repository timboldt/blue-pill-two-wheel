# Pinouts

## Blue Pill

* As a point of reference in this doc, the USB connector is at the "top".
* The left side is 5V tolerant.
* The right side is not 5V tolerant, except for PB10/11.

Left side:

```
PB12      (SPI2 SS?)
PB13  --> SPI2 CLK
PB14  <-- SPI2 MISO
PB15  --> SPI2 MOSI
PA8   <-- Left encoder A
PA9   <-- Left encoder B
PA10  --> Left Motor En A
PA11  --> Left Motor En B
PA12  --> Right Motor En A
PA15  --> Right Motor En B
PB3   --> Segger SWO
PB4
PB5
PB6   <-- Right encoder A
PB7   <-- Right encoder B
PB8   <-- Reserved: I2C1 SCL
PB9   <-> Reserved: I2C1 SDA
5V    <-- Power Supply
GND   <-- Power Supply
3V3
```

Right side:

```
GND
GND
3V3
NRST   <-- Segger RESET
PB11   <-> I2C2 SDA
PB10   --> I2C2 SCL
PB1
PB0
PA7    --> Reserved: SPI1 MOSI
PA6    <-- Reserved: SPI1 MISO
PA5    --> Reserved: SPI1 CLK
PA4    --> Reserved: SPI1 NSS
PA3    <-- Reserved: UART2 RX
PA2    --> Reserved: UART2 TX
PA1    --> Motor PWM2
PA0    --> Motor PWM1
PC15   x-x
PC14   x-x
PC13   --> LED
VBAT   x-x
```

Bottom:

```
3V3         --> Segger VTREF
SWDIO(PA13) <-> Segger SWDIO
SWCLK(PA14) <-- Segger SWCLK
GND         --- Segger GND
```

## Segger 20-pin Connector

* [Segger docs](https://www.segger.com/products/debug-probes/j-link/technology/interface-description/)
* Top left is 1.
* Tab faces left.

![20-pin pinout](https://www.segger.com/fileadmin/images/products/J-Link/Interface_Description/181129_SWD.svg)

```
VTREF  x
x      GND
x      GND
SWDIO  GND
SWCLK  GND
x      GND
SWO    GND
RESET  GND
x      GND
5V     GND
```

## Segger 10-pin Connector

* [Segger docs](https://www.segger.com/products/debug-probes/j-link/accessories/adapters/9-pin-cortex-m-adapter/).
* Top left is 1.
* Tab faces left.

![pinout graphic](https://www.segger.com/fileadmin/images/products/J-Link/Accesory/Adapters/J-Link_9-pin_Cortex-M_Adapter.png)

```
VTREF   SWDIO
GND     SWCLK
GND     SWO
x       x
x       RESET
```
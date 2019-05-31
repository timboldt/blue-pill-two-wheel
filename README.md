# bluepill2wheel

This is a reimplementation of my original Arduino-based Two-Wheel Balancing Bot, this time using libopencm3 and plain C.

Project status: The hardware is complete and all peripherals are working from
code. The PID logic is still a hack and needs work before it will balance
properly.

### Disclaimer

This is not an officially supported Google product.

### Pinouts

TODO(tboldt): Update these based on latest h/w changes.

```
PA0  - Encoder 1 Channel A
PA1  - Encoder 1 Channel B
PA2  - Motor 2 Forward
PA3  - Motor 2 Reverse
PA4  - Motor 1 Forward
PA5  - Motor 1 Reverse
PA6  - Encoder 1 Channel A
PA7  - Encoder 1 Channel B

PA9  - USART1 TX
PA10 - USART1 RX

PB6  - Motor 1 PWM on TIM4 Ch 1
PB7  - Motor 2 PWM on TIM4 Ch 2
PB8  - RESERVED
PB9  - RESERVED
PB10 - I2C SCL
PB11 - I2C SDA
PB12 - SPI2 Slave Select
PB13 - SPI2 SCK
PB14 - SPI2 MISO
PB15 - SPI2 MOSI

PC13 - LED
```
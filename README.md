# bluepill2wheel
Reimplementation of Two-Wheel Balancing Bot using STM32CubeMX and plain C.

### Pinouts

```
[TODO] PA0  - Encoder 1 Channel A
[TODO] PA1  - Encoder 1 Channel B
PA2  - Motor 1 Channel 1
PA3  - Motor 1 Channel 2
PA4  - Motor 2 Channel 1
PA5  - Motor 2 Channel 2
[TODO] PA6  - Encoder 1 Channel A
[TODO] PA7  - Encoder 1 Channel B

PA9  - USART1 TX
PA10 - USART1 RX

PB6  - Motor 1 PWM on TIM4 Ch 1
PB7  - Motor 2 PWM on TIM4 Ch 2
PB8  - RESERVED
PB9  - RESERVED
PB10 - I2C SCL
PB11 - I2C SDA
[TODO] PB12 - SPI2 Slave Select
[TODO] PB13 - SPI2 SCK
[TODO] PB14 - SPI2 MISO
[TODO] PB15 - SPI2 MOSI

PC13 - LED
```
# Adapted from https://github.com/ve3wwg/stm32f103c8t6.

BINARY		= bin/bluepill2wheel
SRCFILES	= \
	src/main.c \
	src/led.c

all: elf bin

include Makefile.incl
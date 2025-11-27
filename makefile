.PHONY: clean flash

TARGET_NAME := main
OUTPUT_DIRECTORY := build
SOURCE_DIRECTORY := src
INCLUDE_DIRECTORY := include
TARGET_PLATFORM := atmega2560

SOURCES := $(shell find $(SOURCE_DIRECTORY) -name '*.c')

OBJECTS := $(SOURCES:%.c=%.o)

#Transform the binary file into a intel hex file to be ready to flash
$(OUTPUT_DIRECTORY)/$(TARGET_NAME).hex: $(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin

	avr-objcopy -O ihex -R .eeprom $(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin $(OUTPUT_DIRECTORY)/$(TARGET_NAME).hex

#link the object files into the binary
$(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin: $(OBJECTS)
	avr-gcc -o $(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin $(OUTPUT_DIRECTORY)/$(OBJECTS) -mmcu=$(TARGET_PLATFORM)

#compile each .c file individually
$(OBJECTS): $(INCLUDES) %.o :%.c
	mkdir -p $(OUTPUT_DIRECTORY)/$(@D)
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(TARGET_PLATFORM) -c $< -o $(OUTPUT_DIRECTORY)/$@ -I$(INCLUDE_DIRECTORY)

clean:
	-rm -rf build/

flash:

	sudo avrdude -v -D -p m2560 -c stk500v2 -P /dev/ttyACM0 -b 115200 -F -U flash:w:$(TARGET_NAME).hex

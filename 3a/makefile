.PHONY: clean flash

CC:=avr-gcc
LD:=avr-ld
TARGET_NAME := 3a
OUTPUT_DIRECTORY := build
SOURCE_DIRECTORY := src
INCLUDE_DIRECTORY := ../include
INCLUDE_DIRECTORY += ../include/arduino
INCLUDE_FLAG := $(addprefix -I, $(INCLUDE_DIRECTORY))
TARGET_PLATFORM := atmega2560

CFLAGS:=

SOURCES := $(shell find $(SOURCE_DIRECTORY) -name '*.cpp')
C_SOURCES := $(shell find $(SOURCE_DIRECTORY) -name '*.c')
ASM_OBJECTS := $(shell find $(SOURCE_DIRECTORY) -name '*.S')

CPP_OBJECTS := $(SOURCES:%.cpp=%.o)
OBJECTS := $(C_SOURCES:%.c=%.o)
OBJECTS_TO_LINK := $(addprefix $(OUTPUT_DIRECTORY)/, $(OBJECTS))
OBJECTS_TO_LINK += $(addprefix $(OUTPUT_DIRECTORY)/, $(CPP_OBJECTS))
OBJECTS_TO_LINK += $(ASM_OBJECTS)

#Transform the binary file into a intel hex file to be ready to flash
$(OUTPUT_DIRECTORY)/$(TARGET_NAME).hex: $(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin

	avr-objcopy -O ihex -R .eeprom $(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin $(OUTPUT_DIRECTORY)/$(TARGET_NAME).hex

#link the object files into the binary
$(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin: $(OBJECTS) $(CPP_OBJECTS)
	$(CC) -o $(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin $(OBJECTS_TO_LINK) -mmcu=$(TARGET_PLATFORM) -Wl,-Map=$(OUTPUT_DIRECTORY)/$(TARGET_NAME).map

#compile each .cpp file individually
$(CPP_OBJECTS): $(INCLUDES) %.o :%.cpp 
	mkdir -p $(OUTPUT_DIRECTORY)/$(@D)
	$(CC) -Os -DF_CPU=16000000UL -mmcu=$(TARGET_PLATFORM) -c $< -o $(OUTPUT_DIRECTORY)/$@ $(INCLUDE_FLAG) $(CFLAGS)

#compile each .c file individually
$(OBJECTS): $(INCLUDES) %.o :%.c
	mkdir -p $(OUTPUT_DIRECTORY)/$(@D)
	$(CC) -Os -DF_CPU=16000000UL -mmcu=$(TARGET_PLATFORM) -c $< -o $(OUTPUT_DIRECTORY)/$@ $(INCLUDE_FLAG) $(CFLAGS)

clean:
	-rm -rf build/

flash:

	avrdude -v -D -p m2560 -c stk500v2 -P /dev/ttyACM0 -b 115200 -F -U flash:w:$(OUTPUT_DIRECTORY)/$(TARGET_NAME).hex
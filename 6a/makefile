.PHONY: clean flash

CC:=avr-gcc
LD:=avr-ld
TARGET_NAME := 6a
OUTPUT_DIRECTORY := build
SOURCE_DIRECTORY := src
ARDUINO_DIRECTORY := ../common
INCLUDE_DIRECTORY := ../include
INCLUDE_DIRECTORY += ../include/arduino
INCLUDE_FLAG := $(addprefix -I, $(INCLUDE_DIRECTORY))
TARGET_PLATFORM := atmega2560

CFLAGS:= -DTARGET_NAME=\"$(TARGET_NAME)\"

SOURCES := $(shell find $(SOURCE_DIRECTORY) -name '*.cpp')
SOURCES += $(shell find $(ARDUINO_DIRECTORY) -name '*.cpp')
C_SOURCES := $(shell find $(SOURCE_DIRECTORY) -name '*.c')
C_SOURCES := $(shell find $(ARDUINO_DIRECTORY) -name '*.c')
ASM_OBJECTS := $(shell find $(ARDUINO_DIRECTORY) -name '*.S')

CPP_OBJECTS := $(SOURCES:%.cpp=%.o)
OBJECTS := $(C_SOURCES:%.c=%.o)
OBJECTS_TO_LINK += $(CPP_OBJECTS)
OBJECTS_TO_LINK += $(OBJECTS)
OBJECTS_TO_LINK += $(ASM_OBJECTS)

#Transform the binary file into a intel hex file to be ready to flash
$(OUTPUT_DIRECTORY)/$(TARGET_NAME).hex: $(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin

	avr-objcopy -O ihex -R .eeprom $(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin $(OUTPUT_DIRECTORY)/$(TARGET_NAME).hex

#link the object files into the binary
$(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin: $(OBJECTS_TO_LINK)
	mkdir -p $(OUTPUT_DIRECTORY)
	$(CC) -o $(OUTPUT_DIRECTORY)/$(TARGET_NAME).bin -Wl,-Map=$(OUTPUT_DIRECTORY)/$(TARGET_NAME).map -mmcu=$(TARGET_PLATFORM) $(OBJECTS_TO_LINK) 

#compile each .cpp file individually
$(CPP_OBJECTS): $(INCLUDES) %.o :%.cpp 
	$(CC) -Os -DF_CPU=16000000UL -mmcu=$(TARGET_PLATFORM) -c $< -o $@ $(INCLUDE_FLAG) $(CFLAGS)

#compile each .c file individually
$(OBJECTS): $(INCLUDES) %.o :%.c
	$(CC) -Os -DF_CPU=16000000UL -mmcu=$(TARGET_PLATFORM) -c $< -o $@ $(INCLUDE_FLAG) $(CFLAGS)

clean:
	-rm -rf build/ ../*.o

flash:

	avrdude -v -D -p m2560 -c stk500v2 -P /dev/ttyACM0 -b 115200 -F -U flash:w:$(OUTPUT_DIRECTORY)/$(TARGET_NAME).hex
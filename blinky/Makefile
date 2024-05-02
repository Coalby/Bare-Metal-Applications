CFLAGS		?=	-I src/include \
				-mcpu=cortex-m4
CC 			= 	arm-none-eabi-gcc

LINK_SRC	?=	linker.ld
LDFLAGS		?=	-T $(LINK_SRC) -nostartfiles -nostdlib --specs nano.specs

SOURCE_DIR	=	src
SOURCES		= 	$(SOURCE_DIR)/main.c
BUILD_DIR	= 	build

.PHONY: all build firmware.elf firmware.bin build-dir flash clean

all: build

build: build-dir firmware.bin

main.o: build-dir $(SOURCES)
	$(CC) $(SOURCES) -c $(CFLAGS) -o $(BUILD_DIR)/$@

firmware.elf: main.o
	$(CC) $(LDFLAGS) $(BUILD_DIR)/$< -o $(BUILD_DIR)/$@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $(BUILD_DIR)/$< $(BUILD_DIR)/$@

flash: firmware.bin
	st-flash --reset write $(BUILD_DIR)/$< 0x8000000

build-dir:
	mkdir $(BUILD_DIR)

clean:
	rm -rf build
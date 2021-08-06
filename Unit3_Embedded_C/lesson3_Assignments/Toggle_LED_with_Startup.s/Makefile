#prepared by Mahmoud Magdy Ayoub (learn-in-depth)
CC=arm-none-eabi-
CFLAGS=-gdwarf-2 -mcpu=cortex-m3
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
Project_Name=Toggle_LED_on_ARM_CortexM3

all:$(Project_Name).bin

startup.o: startup.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@ 

$(Project_Name).elf: $(OBJ) startup.o
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) startup.o -o $@ -Map=Map_file.map

$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@ 

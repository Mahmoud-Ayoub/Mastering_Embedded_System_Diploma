#prepared by Mahmoud Magdy Ayoub (learn-in-depth)
CC=arm-none-eabi-
CFLAGS=-gdwarf-2 -g -mcpu=cortex-m4
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
Project_Name=Toggle_LED_on_ARM_CortexM4

all:$(Project_Name).bin

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@ 

$(Project_Name).elf: $(OBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) -o $@ -Map=Map_file.map
	cp $(Project_Name).elf $(Project_Name).axf

$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@ 

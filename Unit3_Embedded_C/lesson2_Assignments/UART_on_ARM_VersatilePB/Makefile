#prepared by Mahmoud Magdy Ayoub (learn-in-depth)
CC=arm-none-eabi-
CFLAGS=-g -mcpu=arm926ej-s
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all:learn_in_depth.bin

startup.o: startup.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@ 

learn_in_depth.elf: $(OBJ) startup.o
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) startup.o -o $@ -Map=Map_file.map

learn_in_depth.bin: learn_in_depth.elf
	$(CC)objcopy.exe -O binary $< $@ 

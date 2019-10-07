if avr-gcc -g -Os -mmcu=avr6 -c main.cpp -Wno-write-strings
then
	avr-size main.o --mcu=avr6 --radix=10
	avr-gcc -g -mmcu=avr6 -Wl,--defsym,__heap_end=0 -o ../../bin/ntios-atmega2560.elf main.o
	avr-objcopy -j .text -j .data -O binary ../../bin/ntios-atmega2560.elf ../../bin/ntios-atmega2560.bin
else
	echo "Compiler errors: Not linking."
fi

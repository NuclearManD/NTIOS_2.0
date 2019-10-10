if avr-g++ -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -mmcu=atmega2560 -DF_CPU=16000000L platform.c -o main.o
then
	avr-gcc -g -mmcu=atmega2560 -Wl,--defsym,__heap_end=0 -o ../../bin/ntios-atmega2560.elf main.o
	avr-size ../../bin/ntios-atmega2560.elf --mcu=atmega2560 --radix=10
	avr-objcopy -j .text -j .data -O binary ../../bin/ntios-atmega2560.elf ../../bin/ntios-atmega2560.bin
else
	echo "Compiler errors: Not linking."
fi
exit
avr-g++ -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -flto -w -x c++ -E -CC -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10808 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR -I/home/nuclaer/perm/arduino-1.8.8/hardware/arduino/avr/cores/arduino -I/home/nuclaer/perm/arduino-1.8.8/hardware/arduino/avr/variants/mega /tmp/arduino_build_541442/sketch/sketch_oct09a.ino.cpp -o /dev/null

/avr-g++ -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -flto -w -x c++ -E -CC -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10808 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR -I/home/nuclaer/perm/arduino-1.8.8/hardware/arduino/avr/cores/arduino -I/home/nuclaer/perm/arduino-1.8.8/hardware/arduino/avr/variants/mega /tmp/arduino_build_541442/sketch/sketch_oct09a.ino.cpp -o /tmp/arduino_build_541442/preproc/ctags_target_for_gcc_minus_e.cpp
/home/nuclaer/perm/arduino-1.8.8/tools-builder/ctags/5.8-arduino11/ctags -u --language-force=c++ -f - --c++-kinds=svpf --fields=KSTtzns --line-directives /tmp/arduino_build_541442/preproc/ctags_target_for_gcc_minus_e.cpp
Compiling sketch...
/home/nuclaer/perm/arduino-1.8.8/hardware/tools/avr/bin/avr-g++ -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10808 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR -I/home/nuclaer/perm/arduino-1.8.8/hardware/arduino/avr/cores/arduino -I/home/nuclaer/perm/arduino-1.8.8/hardware/arduino/avr/variants/mega /tmp/arduino_build_541442/sketch/sketch_oct09a.ino.cpp -o /tmp/arduino_build_541442/sketch/sketch_oct09a.ino.cpp.o
Compiling libraries...

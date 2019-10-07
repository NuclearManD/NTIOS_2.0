avrdude -Cavrdude.conf -v -patmega2560 -cwiring -P/dev/ttyACM0 -b115200 -D -Uflash:w:../ntios-atmega2560.elf:e

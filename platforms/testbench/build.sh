if g++ -c main.cpp -o main.o -Wno-write-strings
then
	g++ -c platform.c -o platform.o -Wno-write-strings
	g++ -o ../../bin/ntios-testbench.elf main.o platform.o
else
	echo "Compiler errors: Not linking."
fi

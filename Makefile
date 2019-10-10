
# generic compiler options
G_CFLAGS = -Wall
BUILD = ./build
BIN_DIR = ./bin
BUILD_OBJ = $(BUILD)/obj
INCLUDES = -I./include
NTIOS_PREFIX = ntios

default: testbench

build_base:
	mkdir build/obj -p
	mkdir $(BIN_DIR) -p
	python3 build_c.py
	$(CC) $(G_CFLAGS) $(P_CFLAGS) $(INCLUDES) -c NTIKernel.cpp -o $(BUILD_OBJ)/NTIKernel.o
	$(CC) $(G_CFLAGS) $(P_CFLAGS) $(INCLUDES) -c drivers/drivers.c -o $(BUILD_OBJ)/drivers.o
	$(CC) $(G_CFLAGS) $(P_CFLAGS) $(INCLUDES) -c programs/program.c -o $(BUILD_OBJ)/program.o


# testbench vars and target
testbench: CC = g++
testbench: P_CFLAGS = -g
testbench: OUTFILE = $(BIN_DIR)/$(NTIOS_PREFIX)-tb.elf
testbench: build_base
	$(CC) $(G_CFLAGS) $(P_CFLAGS) $(INCLUDES) -c platforms/testbench/platform.c -o $(BUILD_OBJ)/platform.o
	$(CC) $(G_CFLAGS) $(P_CFLAGS) $(BUILD_OBJ)/NTIKernel.o $(BUILD_OBJ)/platform.o $(BUILD_OBJ)/drivers.o $(BUILD_OBJ)/program.o -o $(OUTFILE)

clean:
	rm -rf ./bin
	rm -rf ./build

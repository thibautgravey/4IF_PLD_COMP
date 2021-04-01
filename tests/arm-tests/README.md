# ARM Emulation with QEMU

Here, you can emulate an arm execution using qemu. Tested on Ubuntu 20.04
This is just a way to execute a single file code in arm, not a framework for batch testing

## Installation 

You will need to install qemu-system-arm: 

`apt install quemu-system-arm`

You also need arm-none-eabi to use arm instructions. 

`apt install gcc-arm-none-eabi`

## Get ARM assembly code from .c file

`arm-none-eabi-gcc SOURCE_FILE.c -S`

you can also execute c code on arm directly with `make launch_qemu_c`


## Execute assembly code on arm architecture

You need to have your assembly code in src/test.s

then, run `make` in a terminal

in qemu, go to view > show tabs. The output is in serial0

CROSS_COMPILE ?= arm-none-eabi
TARGET_SYSTEM = qemu-system-arm
SRC = src

AOPS = --warn --fatal-warnings 
COPS = -Wall -Werror -O2 -nostdlib -notestfiles -ffreestanding

#launch qemu with an assembly code file (.s)

launch_qemu_as: $(SRC)/test.s memmap
	$(CROSS_COMPILE)-as $(AOPS) $(SRC)/test.s -o test.o
	$(CROSS_COMPILE)-ld  test.o -T memmap -o arm_assembly.elf
	$(CROSS_COMPILE)-objdump -D arm_assembly.elf > arm_assembly.list
	$(CROSS_COMPILE)-objcopy arm_assembly.elf -O binary arm_assembly.bin
	$(TARGET_SYSTEM) -M versatilepb -m 128M -kernel arm_assembly.bin
	
#launch qemu with a c code file  (.c) 

launch_qemu_c: $(SRC)/test.c startup.s test.ld
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g $(SRC)/test.c -o test.o
	arm-none-eabi-ld -T test.ld test.o startup.o -o test.elf
	arm-none-eabi-objcopy -O binary test.elf test.bin
	qemu-system-arm -M versatilepb -m 128M  -kernel test.bin
	
clean: 
	rm -f *.elf *.bin *.list *.o 

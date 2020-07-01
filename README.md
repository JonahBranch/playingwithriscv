# playing with riscv
These are just my experiments working with the Risc-V instruction set.

My goal is to write my own assembly to run on the Longan Nano. "blink.hex" is working firmware compiled from c which will blink the on board LED on and off.
I am writing a program (hex2riscv.c) to read the hex file, extract the machine code, and then parse the machine code into assembly. From there I can study the code
and use that knowledge to write my own assembly. I will probably write my own assembler as well.

So far all my program does is read the hex file and assign some names to a few 32 bit instructions.

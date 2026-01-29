# Intro to Assembly

```c
assembly: main.c
	riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld main.c -S

binary: main.s main.ld
	riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld main.s -o main.elf
	riscv64-unknown-elf-objcopy -O binary main.elf main.bin

printbin: main.bin
	xxd -e -c 4 -g 4 main.bin

startqemu: main.elf
	qemu-system-riscv32 -S -M virt -nographic -bios none -kernel main.elf -gdb tcp::1234

connectGDB: main.elf
	riscv64-elf-gdb main.elf -ex "target remote localhost:1234" -ex "break _start" -ex "continue" - q

clean:
	rm -rf *.bin *.elf

```

so in the **assembly** section of the above makefile we added, we say the gcc generate the assembly code from main.c and put it in _main.s_, do nothing more nothing less


![alt text](image-5.png)

the line `riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld main.c -S` resulted in this large assembly but most of the content in the assembly file is atttributes(this is because of -ggdb flag(this integrates binary so that we can work with gdb)).

>attribute: 

so i removed this flag and the resulting assembly is smaller then previous one.

```c
	.file	"main.c"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	siliwho
	.type	siliwho, @function
siliwho:
	addi	sp,sp,-16
	sw	ra,12(sp)
	sw	s0,8(sp)
	addi	s0,sp,16
	li	a5,3
	mv	a0,a5
	lw	ra,12(sp)
	lw	s0,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	siliwho, .-siliwho
	.ident	"GCC: (g1b306039a) 15.1.0"
	.section	.note.GNU-stack,"",@progbits
```
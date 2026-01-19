---
tags: [pointers, memory, hardware]
---

## How to convert the code to binary

The command below compiles **RISC-V 32-bit assembly code** into an ELF binary:

```bash
riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tmain.ld main.s -o main.elf
```

> Even though the compiler prefix is `riscv64`, it can still generate **RV32** binaries when `-march=rv32*` is specified.

Explanation of Each Argument

- `-O0`
  - Disables all compiler optimizations.
  - Keeps the generated code **close to the written assembly/C logic**.
  - Very useful for:
    - Learning
    - Debugging
    - Stepping through instructions in GDB

- `-ggdb`
  - Adds **debug symbols** specifically optimized for **GDB**.
  - Allows you to:
    - Inspect registers
    - Set breakpoints
    - Step instruction-by-instruction

  - Does **not** affect execution behavior, only debugging.

- `-nostdlib`
  - Prevents linking of:
    - Standard C library (`libc`)
    - Startup files (`crt0`, `_start`, etc.)

  - Required for:
    - Bare-metal programs
    - OS kernels
    - Bootloaders

  - You must provide:
    - Your own entry point
    - Your own linker script

- `-march=rv32i`
  - Specifies the **Instruction Set Architecture (ISA)**.
  - `rv32i` means:
    - `rv32` → 32-bit RISC-V
    - `i` → base integer instruction set only

  - No support for:
    - Multiplication (`M`)
    - Atomics (`A`)
    - Floating point (`F/D`)
    - Compressed instructions (`C`)

  This keeps the CPU model **minimal and educational**.

- `-mabi=ilp32`
  - Specifies the **Application Binary Interface (ABI)**.
  - Defines:
    - Size of data types
    - Calling convention
    - Register usage
    - Stack layout

  For `ilp32`:
  - `int` = 32 bits
  - `long` = 32 bits
  - `pointer` = 32 bits
  * This ABI **matches RV32** and uses **no floating-point registers**.

  > `-march` defines _what instructions exist_  
  > `-mabi` defines _how functions communicate_

  ! `-mabi` **must be compatible** with `-march`.
  - Valid:

  ```bash
  -march=rv32i -mabi=ilp32
  ```

  - Invalid:

  ```bash
  -march=rv32i -mabi=ilp32d   # requires D (double FP) extension
  ```

- `-Wl,-Tmain.ld`
  - Passes arguments directly to the **linker (`ld`)**.
  - `-Tmain.ld` tells the linker to use a **custom linker script**.
  - The linker script defines:
    - Memory layout
    - Entry point
    - Section placement (`.text`, `.data`, `.bss`, stack, etc.)

  This is **mandatory** in bare-metal development.

- `main.s`
  - Input assembly source file.
  - Typically contains:
    - `_start` label
    - Handwritten RISC-V assembly

- `-o main.elf`
  - Specifies the output file.
  - `main.elf` is an **ELF executable**, not raw binary.
  - Can be:
    - Loaded into QEMU
    - Debugged using GDB
    - Converted to raw binary using `objcopy`

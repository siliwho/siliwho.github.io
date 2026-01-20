---
layout: default
title: "Kernel Compilation Guide"
category: notes
---

# ~/notes/kernel-compilation.md

Hello i added this 

## 1. Prerequisites

Install the following packages before starting:

- `build-essential`
- `libncurses-dev`
- `bison`

## 2. Compilation Command

Run the following in the source directory:

```bash
make menuconfig

make -j$(nproc) #this gives all the cores to process
```

![Kernel Menuconfig](https://raw.githubusercontent.com/siliwho/documentry/main/content/assets/kernel_menuconfig.png)

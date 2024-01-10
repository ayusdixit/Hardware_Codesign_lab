 # Lab-1

## Introduction
This repository contains a simple guide for compiling and running a "Hello, World!" program on both x86_64 and 32-bit ARM architectures.

## Prerequisites
- Ensure you have a Linux environment.
- Run `uname -m` to check your machine architecture.

## Setup for x86_64
```bash
sudo apt install gcc make gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi
vi helloworld.c
gcc helloworld.c -o helloworld-x86_64
file helloworld-x86_64
./helloworld-x86_64
```
## Setup for 32-bit ARM
```bash
arm-linux-gnueabi-gcc helloworld.c -o helloworld-arm -static
file helloworld-arm
readelf -h helloworld-arm

sudo apt install qemu-system-arm qemu
arm-linux-gnueabihf-gcc -static -o hello hello.c
qemu-arm hello

````

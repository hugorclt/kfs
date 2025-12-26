FROM --platform=linux/amd64 ubuntu:22.04

RUN apt update && apt install -y \
    build-essential \
    gcc \
    nasm \
    grub-pc-bin \
    grub-common \
    xorriso \
    qemu-system-x86 \
    make
WORKDIR /kernel

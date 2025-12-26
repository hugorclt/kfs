#!/bin/bash
set -e

echo "🔧 Building x86 kernel toolchain..."
docker build --platform=linux/amd64 -t kfs-x86 .

echo "⚙️  Compiling kernel inside x86 container..."
docker run --rm --platform=linux/amd64 -v "$PWD:/kernel" kfs-x86 make

echo "🚀 Running kernel in host QEMU..."
qemu-system-i386 -cdrom kfs.bin.iso -display cocoa


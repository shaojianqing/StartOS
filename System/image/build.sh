#!/bin/sh

rm -rf Image.bin data

mkdir data

sudo dd if=/dev/zero of=Image.bin bs=1M count=8

sudo mkfs.minix -n14 Image.bin

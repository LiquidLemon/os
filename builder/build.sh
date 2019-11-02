#!/bin/bash

mkdir -p /build/binutils
cd /build/binutils
/src/binutils/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
make -j$(nproc)
make install

which -- $TARGET-as || (echo $TARGET-as not in PATH && exit 1)
mkdir -p /build/gcc
cd /build/gcc
/src/gcc/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j$(nproc)
make all-target-libgcc -j$(nproc)
make install-gcc
make install-target-libgcc

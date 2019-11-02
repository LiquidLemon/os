FROM debian

ENV BINUTILS_VERSION 2.33.1
ENV GCC_VERSION 8.3.0

ENV TARGET i686-elf

ENV PREFIX /usr/local/cross
ENV PATH="${PREFIX}/bin:${PATH}"

RUN apt-get update && \
    apt-get install -y build-essential bison flex libgmp3-dev libmpc-dev \
                   libmpfr-dev texinfo libisl-dev file wget

WORKDIR /src

RUN wget https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.xz /src/binutils -O - | \
    tar -Jx && \
    mv binutils-$BINUTILS_VERSION binutils && \
    mkdir -p /build/binutils && \
    cd /build/binutils && \
    /src/binutils/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror && \
    make -j$(nproc) && \
    make install

RUN which -- $TARGET-as || (echo $TARGET-as not in PATH && exit 1) && \
    wget https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.xz /src/gcc -O - | \
    tar -Jx && \
    mv gcc-$GCC_VERSION gcc && \
    mkdir -p /build/gcc && \
    cd /build/gcc && \
    /src/gcc/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers && \
    make all-gcc -j$(nproc) && \
    make all-target-libgcc -j$(nproc) && \
    make install-gcc && \
    make install-target-libgcc

FROM debian

COPY --from=0 /usr/local/cross /usr/local
RUN apt-get update && apt-get install -y make libisl19 libmpc3 libfl2 grub-common

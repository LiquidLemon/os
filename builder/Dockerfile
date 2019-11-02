FROM debian

ENV BINUTILS_VERSION 2.33.1
ENV GCC_VERSION 8.3.0

RUN apt update && \
    apt install -y build-essential bison flex libgmp3-dev libmpc-dev \
                   libmpfr-dev texinfo libisl-dev file wget

WORKDIR /src

RUN wget https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.xz /src/binutils -O - | \
    tar -Jx && mv binutils-$BINUTILS_VERSION binutils

RUN wget https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.xz /src/gcc -O - | \
    tar -Jx && mv gcc-$GCC_VERSION gcc

COPY ./build.sh /build.sh

CMD ["/build.sh"]

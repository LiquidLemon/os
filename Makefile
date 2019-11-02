export HOSTARCH:=i386

BIN:=$(CURDIR)/tools/bin
export SYSROOT:=$(CURDIR)/sysroot
export DESTDIR:=/usr

export CC:=$(BIN)/i686-elf-gcc --sysroot=$(SYSROOT)
export CFLAGS?=-O2 -g -I$(SYSROOT)/usr/include
export AR:=$(BIN)/i686-elf-ar
export AS:=$(BIN)/i686-elf-as

PROJECTS:=libc kernel

.PHONY: all $(PROJECTS) clean install run debug gdb

all: headers $(PROJECTS)

headers:
	for project in $(PROJECTS); do \
		$(MAKE) -C $$project install-headers; \
	done

$(PROJECTS):
	$(MAKE) -C $@

run:
	qemu-system-i386 -kernel kernel/build/myos.kernel

debug:
	qemu-system-i386 -s -S -kernel kernel/build/myos.kernel

gdb:
	gdb -symbols kernel/build/myos.kernel -ex "target remote localhost:1234"

clean:
	for project in $(PROJECTS); do \
		$(MAKE) -C $$project clean; \
	done
	rm -rf sysroot

install:
	$(MAKE) -C libc install

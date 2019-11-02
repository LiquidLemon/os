BIN:=$(realpath tools/bin)

export CFLAGS?=-O2 -g
export CC=$(BIN)/i686-elf-gcc

PROJECTS:=libc kernel

.PHONY: all $(PROJECTS) clean

all: $(PROJECTS)

$(PROJECTS):
	$(MAKE) -C $@

clean:
	rm -r $(shell find $(PROJECTS) -name build -type d)

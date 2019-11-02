CFLAGS+=-ffreestanding -Wall -Wextra
CPPFLAGS+=-D__is_kernel -Iinclude
LIBS+=-nostdlib -lk -lgcc

TARGET:=build

ARCHDIR=arch/$(HOSTARCH)

ARCH_OBJS:= \
  $(subst .c,.o,$(shell find $(ARCHDIR) -name "*.c")) \
  $(subst .S,.o,$(shell find $(ARCHDIR) -name "*.S")) \
  $(addprefix $(ARCHDIR)/,crtbegin.o crtend.o)

KERNEL_OBJS:= \
  $(subst .c,.o,$(shell find kernel -name "*.c")) \
  $(subst .S,.o,$(shell find kernel -name "*.S"))

OBJS:=$(addprefix $(TARGET)/,$(ARCH_OBJS) $(KERNEL_OBJS))

.PHONY: all clean install-headers

all: $(TARGET)/myos.kernel

$(TARGET)/myos.kernel: $(ARCHDIR)/linker.ld $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -T $< -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS)
	grub-file --is-x86-multiboot $@

$(TARGET)/$(ARCHDIR)/crtbegin.o $(TARGET)/$(ARCHDIR)/crtend.o:
	mkdir -p $(dir $@)
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) --print-file-name $(@F)` && cp "$$OBJ" $@

$(TARGET)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(TARGET)/%.o: %.S
	mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -rf build

install: install-headers

install-headers:
	mkdir -p $(SYSROOT)$(DESTDIR)
	cp -R --preserve=timestamps include/ $(SYSROOT)$(DESTDIR)

# See libc/Makefile for explanation
-include $(shell find $(TARGET) -name '*.d' 2>/dev/null)

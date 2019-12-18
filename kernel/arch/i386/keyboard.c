#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#include <kernel/keyboard.h>
#include <kernel/ports.h>

#include "isr.h"

#define MAX_SCANCODE 0x3A

static const char symbols[] = {
  0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\\', '`',
  0 , '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
  '*', 0, ' ', 0 // incomplete, last is capslock
};


void handle_key(registers regs) {
  uint8_t scancode = inb(KEYBOARD_DATA);
  if (scancode < MAX_SCANCODE) {
    char c = symbols[scancode];
    printf("0x%x %c\n", scancode, isprint(c) ? c : '?');
  }
}

void init_keyboard() {
  register_interrupt_handler(IRQ1, handle_key);
}

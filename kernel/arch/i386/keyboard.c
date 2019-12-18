#include <stdio.h>
#include <stdint.h>

#include <kernel/keyboard.h>
#include <kernel/ports.h>

#include "isr.h"

void handle_key(registers regs) {
  uint8_t keycode = inb(KEYBOARD_DATA);
  printf("Key pressed: %d\n", keycode);
}

void init_keyboard() {
  register_interrupt_handler(IRQ1, handle_key);
}

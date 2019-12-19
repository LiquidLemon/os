#include <stdio.h>
#include <stdint.h>

#include <kernel/timer.h>
#include <kernel/idt.h>
#include <kernel/ports.h>

#include "isr.h"

#define PIT            0x40
#define PIT_CH0        PIT
#define PIT_COMMAND    (PIT + 3)
#define PIT_CMD_CH0    0b00000000
#define PIT_CMD_LOHI   0b00110000
#define PIT_CMD_RATE   0b00000110
#define PIT_CMD_BINARY 0b00000000

uint32_t counter = 0;
uint16_t divisor;
uint32_t ticks_to_wait = 0;

void timer_callback(registers regs __attribute__((unused))) {
  counter++;
  if (ticks_to_wait > 0) {
    ticks_to_wait--;
  }
}

void init_timer(uint32_t frequency) {
  register_interrupt_handler(IRQ0, timer_callback);

  divisor = 1193180 / frequency;

  outb(PIT_COMMAND, PIT_CMD_CH0 | PIT_CMD_LOHI | PIT_CMD_RATE | PIT_CMD_BINARY);
  io_wait();

  uint8_t low = divisor & 0xFF;
  uint8_t high = (divisor >> 8) & 0xFF;

  outb(PIT_CH0, low);
  io_wait();
  outb(PIT_CH0, high);
  io_wait();
}

void sleep(uint32_t ms) {
  ticks_to_wait = ms/(10000.0/divisor) + 1;

  asm ("sti");

  while (ticks_to_wait != 0) {
    asm ("hlt");
  }
}

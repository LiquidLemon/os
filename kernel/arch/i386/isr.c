#include "isr.h"
#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/ports.h>

interrupt_handler interrupt_handlers[256] = {0};

void register_interrupt_handler(
    uint8_t n,
    interrupt_handler handler
) {
  interrupt_handlers[n] = handler;
}

void isr_handler(registers regs) {
  if (interrupt_handlers[regs.int_no] != NULL) {
    interrupt_handlers[regs.int_no](regs);
  } else {
    printf("Unhandled interrupt: %d\n", regs.int_no);
  }
}

void irq_handler(registers regs) {
  if (regs.int_no >= 40) {
    outb(PIC2_COMMAND, PIC_EOI);
  }

  outb(PIC1_COMMAND, PIC_EOI);

  if (interrupt_handlers[regs.int_no] != NULL) {
    interrupt_handlers[regs.int_no](regs);
  } else {
    printf("Unhandled interrupt (IRQ): %d\n", regs.int_no);
  }
}

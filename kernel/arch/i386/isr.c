#include "isr.h"
#include <stdio.h>
#include <kernel/tty.h>

void isr_handler(registers regs) {
  printf("isr%d\n", regs.int_no);
}

void irq_handler(registers regs) {
  printf("Caught irq\n");
}

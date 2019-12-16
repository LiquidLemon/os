#include "isr.h"
#include <stdio.h>

void isr_handler(registers regs) {
  printf("Caught isr\n");
}

void irq_handler(registers regs) {
  printf("Caught irq\n");
}

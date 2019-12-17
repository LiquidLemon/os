#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/tty.h>

void kmain(void) {
  init_gdt();
  init_idt();

  terminal_init();
  printf(
      "            (_)         \n"
      " _ __   ___  _  ___ ___ \n"
      "| '_ \\ / _ \\| |/ __/ _ \\\n"
      "| | | | (_) | | (_|  __/\n"
      "|_| |_|\\___/|_|\\___\\___|\n"
  );

  asm volatile ("int $0x3");
  asm volatile ("int $0x4");
}


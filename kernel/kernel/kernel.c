#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/timer.h>
#include <kernel/keyboard.h>
#include <kernel/shell.h>
#include <kernel/ata.h>
#include <kernel/tty.h>

void kmain(void) {
  terminal_init();
  printf("Terminal initialized\n");

  printf("Setting up GDT...");
  init_gdt();
  printf(" done.\n");

  printf("Setting up IDT...");
  init_idt();
  printf(" done.\n");

  printf("Initializing timer...");
  init_timer(50);
  printf(" done.\n");

  printf("Initializing IDE...");
  ide_init(0x1F0, 0x3F6, 0x170, 0x376, 0);
  printf(" done.\n");

  printf("Initializing keyboard...");
  init_keyboard();
  printf(" done.\n");

  printf("Initializing shell...\n");
  init_shell();
}


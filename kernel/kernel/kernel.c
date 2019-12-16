#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/tty.h>

void kmain(void) {
  init_gdt();

  terminal_init();
  printf(
      "            (_)         \n"
      " _ __   ___  _  ___ ___ \n"
      "| '_ \\ / _ \\| |/ __/ _ \\\n"
      "| | | | (_) | | (_|  __/\n"
      "|_| |_|\\___/|_|\\___\\___|\n"
  );

}


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t * const VGA_MEMORY = (uint16_t *) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

void terminal_init(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = VGA_MEMORY;

  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      terminal_buffer[y * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_column = 0;
    terminal_row = (terminal_row + 1) % VGA_HEIGHT;
    return;
  }

  uint16_t entry = vga_entry(c, terminal_color);
  terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = entry;

  terminal_column++;
  terminal_row = (terminal_row + terminal_column / VGA_WIDTH) % VGA_HEIGHT;
  terminal_column %= VGA_WIDTH;
}

void terminal_print(const char *string) {
  while (string) {
    terminal_putchar(*string++);
  }
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    terminal_putchar(data[i]);
  }
}

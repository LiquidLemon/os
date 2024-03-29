#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/ports.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t * const VGA_MEMORY = (uint16_t *) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

void update_cursor() {
  uint16_t location = terminal_row * 80 + terminal_column;
  outb(0x3D4, 14);
  outb(0x3D5, location >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, location & 0xFF);
}

void terminal_scroll(void) {
  for (size_t y = 1; y < VGA_HEIGHT; y++) {
    memmove(
        &terminal_buffer[(y - 1) * VGA_WIDTH],
        &terminal_buffer[y * VGA_WIDTH],
        2 * VGA_WIDTH
    );
  }

  memset(
      &terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH],
      0,
      2 * VGA_WIDTH
  );
}

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
    terminal_row = terminal_row + 1;
    return;
  }

  if (terminal_row >= VGA_HEIGHT) {
    terminal_scroll();
    terminal_row = VGA_HEIGHT - 1;
  }

  uint16_t entry = vga_entry(c, terminal_color);
  terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = entry;

  terminal_column++;
  terminal_row = (terminal_row + terminal_column / VGA_WIDTH) % VGA_HEIGHT;
  terminal_column %= VGA_WIDTH;

  update_cursor();
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

void terminal_delete_char() {
  if (terminal_column == 0 && terminal_row > 0) {
    terminal_row--;
    terminal_column = VGA_WIDTH - 1;
  }

  if (terminal_column > 0) {
    terminal_column--;
  }

  terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = vga_entry(' ', terminal_color);
  update_cursor();
}

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_init(void);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_print(const char *string);
void terminal_delete_char();

#endif

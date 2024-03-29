#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length) {
  const unsigned char* bytes = (const unsigned char*) data;
  for (size_t i = 0; i < length; i++)
    if (putchar(bytes[i]) == EOF)
      return false;
  return true;
}

static int print_int(int);
static int print_hex(unsigned);

int printf(const char* restrict format, ...) {
  va_list parameters;
  va_start(parameters, format);

  int written = 0;

  while (*format != '\0') {
    size_t maxrem = INT_MAX - written;

    if (format[0] != '%' || format[1] == '%') {
      if (format[0] == '%')
        format++;
      size_t amount = 1;
      while (format[amount] && format[amount] != '%')
        amount++;
      if (maxrem < amount) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(format, amount))
        return -1;
      format += amount;
      written += amount;
      continue;
    }

    const char* format_begun_at = format++;

    if (*format == 'c') {
      format++;
      char c = (char) va_arg(parameters, int /* char promotes to int */);
      if (!maxrem) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(&c, sizeof(c)))
        return -1;
      written++;
    } else if (*format == 's') {
      format++;
      const char* str = va_arg(parameters, const char*);
      size_t len = strlen(str);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(str, len))
        return -1;
      written += len;
    } else if (*format == 'd') {
      format++;
      int num = va_arg(parameters, int);
      written += print_int(num);
    } else if (*format == 'x') {
      format++;
      unsigned num = va_arg(parameters, unsigned);
      written += print_hex(num);
    } else {
      format = format_begun_at;
      size_t len = strlen(format);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(format, len))
        return -1;
      written += len;
      format += len;
    }
  }

  va_end(parameters);
  return written;
}

static int print_int(int num) {
  int count = 0;

  if (num < 0) {
    putchar('-');
    num = -num;
    count++;
  }

  int rest = num / 10;
  int digit = num % 10;

  if (rest != 0) {
    count += print_int(rest);
  }

  putchar(digit + '0');
  count++;
  return count;
}

static const char *hex_digits = "0123456789ABCDEF";

static int print_hex(unsigned num) {
  int count = 0;

  unsigned rest = num >> 4;
  unsigned digit = num & 0xF;

  if (rest != 0) {
    count += print_hex(rest);
  }

  putchar(hex_digits[digit]);
  count++;
  return count;
}

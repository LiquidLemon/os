#ifndef  _KERNEL_GDT_H
#define  _KERNEL_GDT_H

#include <stdint.h>

typedef struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;

} __attribute__((packed)) gdt_entry;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_pointer;

void init_gdt(void);

#endif

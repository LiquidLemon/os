#include <stdint.h>
#include <stddef.h>

#include <kernel/gdt.h>

extern void gdt_flush(uint32_t);

void init_gdt(void);
static void gdt_set_gate(size_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry gdt_entries[5];
gdt_pointer gdt_ptr;

void init_gdt(void) {
  gdt_ptr.limit = sizeof(gdt_entry) * 5 - 1;
  gdt_ptr.base = (uint32_t) &gdt_entries;

  gdt_set_gate(0, 0, 0, 0, 0);
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

  gdt_flush((uint32_t) &gdt_ptr);
}


static void gdt_set_gate(
  size_t num,
  uint32_t base,
  uint32_t limit,
  uint8_t access,
  uint8_t gran
) {
  gdt_entries[num].base_low    = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high   = (base >> 24) & 0xFF;

  gdt_entries[num].limit_low   = (limit & 0xFFFF);
  gdt_entries[num].granularity = (limit >> 16) & 0x0F;

  gdt_entries[num].granularity |= gran & 0xF0;
  gdt_entries[num].access      = access;
}


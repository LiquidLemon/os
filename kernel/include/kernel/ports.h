#ifndef _KERNEL_PORTS_H
#define _KERNEL_PORTS_H

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define PIC_EOI 0x20

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#define KEYBOARD_DATA   0x60


static inline void outb(uint16_t port, uint8_t val) {
  asm volatile ("outb %1, %0" : : "dN"(port), "a"(val));
}

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));

  return ret;
}

static inline void io_wait(void) {
  asm volatile ("outb %%al, $0x80" :: "a"(0));
}

static inline void outw(uint16_t port, uint16_t val)
{
  asm volatile ("outw %1, %0" : : "dN" (port), "a" (val));
}

static inline uint16_t inw(uint16_t port)
{
  uint32_t ret;
  asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

static inline void outl(uint16_t port, uint32_t val)
{
  asm volatile ("outl %1, %0" : : "dN" (port), "a" (val));
}

static inline uint32_t inl(uint16_t port)
{
  uint32_t ret;
  asm volatile("inl %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

#endif

#include <stdint.h>

#include <kernel/date.h>
#include <kernel/ports.h>

#define CMOS_IN 0x70
#define CMOS_OUT 0x71

#define CMOS_SECONDS 0x00
#define CMOS_MINUTES 0x02
#define CMOS_HOURS   0x04
#define CMOS_DAY     0x07
#define CMOS_MONTH   0x08
#define CMOS_YEAR    0x09

#define CMOS_BINARY  0x02
#define CMOS_24HOUR  0x04

uint8_t get_rtc_reg(uint8_t reg) {
  outb(CMOS_IN, reg);
  return inb(CMOS_OUT);
}

uint8_t convert_bcd(uint8_t raw) {
  return (raw & 0xF) + 10 * (raw >> 4);
}

datetime get_date() {
  outb(CMOS_IN, CMOS_BINARY | CMOS_24HOUR);

  datetime date = {
    .second = convert_bcd(get_rtc_reg(CMOS_SECONDS)),
    .minute = convert_bcd(get_rtc_reg(CMOS_MINUTES)),
    .hour = convert_bcd(get_rtc_reg(CMOS_HOURS)),
    .day = convert_bcd(get_rtc_reg(CMOS_DAY)),
    .month = convert_bcd(get_rtc_reg(CMOS_MONTH)),
    .year = 2000 + convert_bcd(get_rtc_reg(CMOS_YEAR)),
  };

  return date;
}

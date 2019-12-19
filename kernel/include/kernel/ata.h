#ifndef _KERNEL_ATA_H
#define _KERNEL_ATA_H

#include <stddef.h>
#include <stdint.h>

#define ATA_READ 0x00
#define ATA_WRITE 0x01

void ide_init(uint32_t BAR0, uint32_t BAR1, uint32_t BAR2, uint32_t BAR3, uint32_t BAR4);
uint8_t ide_ata_access(uint8_t direction, uint8_t drive, uint32_t lba, uint32_t numsects, uint16_t * data);
void ide_print_summary();

#endif //ATA_H

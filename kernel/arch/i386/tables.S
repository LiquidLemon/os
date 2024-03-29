.global gdt_flush
.global idt_flush

gdt_flush:
  movl 4(%esp), %eax
  lgdt (%eax)

  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movw %ax, %ss

  jmp $0x08, $gdt_flush_ret

gdt_flush_ret:
  ret

idt_flush:
  movl 4(%esp), %eax
  lidt (%eax)
  ret

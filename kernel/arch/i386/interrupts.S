.macro ISR_NOERRCODE num=0
.global isr\num
  isr\num:
  cli
  push $0
  push $\num
  jmp isr_common_stub
.endm

.macro ISR_ERRCODE num=0
.global isr\num
  isr\num:
  cli
  push $\num
  jmp isr_common_stub
.endm

.macro IRQ num=0, entry_no=0
.global irq\num
  irq\num:
  cli
  push $0
  push $\entry_no
  jmp irq_common_stub
.endm

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_ERRCODE 30
ISR_NOERRCODE 31

IRQ 0 32
IRQ 1 33
IRQ 2 34
IRQ 3 35
IRQ 4 36
IRQ 5 37
IRQ 6 38
IRQ 7 39
IRQ 8 40
IRQ 9 41
IRQ 10 42
IRQ 11 43
IRQ 12 44
IRQ 13 45
IRQ 14 46
IRQ 15 47

isr_common_stub:
  pusha

  movw %ds, %ax
  pushl %eax

  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  call isr_handler

  popl %eax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  popa
  addl $8, %esp
  sti
  iret

irq_common_stub:
  pusha

  movw %ds, %ax
  pushl %eax

  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  call irq_handler

  popl %eax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  popa
  addl $8, %esp
  sti
  iret

global jumpUsermode

; Edited from: https://wiki.osdev.org/Getting_to_Ring_3
jumpUsermode:
  cli  ; disable interrupts to make sure the jump goes uninterrupted

  pop ebx  ; instruction pointer to return to
  mov ax, (4 * 8) | 3 ; ring 3 data (GDT) with bottom 2 bits set for ring 3
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax ; SS is handled by iret

  ; set up the stack frame iret expects
  mov eax, esp
  push (4 * 8) | 3 ; data selector in GDT
  push eax ; current esp
  pushf ; eflags

  pop eax
  or eax, 0x200  ; enable interrupts register (will only happen after jump)
  push eax

  push (3 * 8) | 3 ; code selector (GDT, ring 3 code with bottom 2 bits set for ring 3)
  push ebx
  iret  ; jumps to ebx (function address), enables interrupts and will be in user mode

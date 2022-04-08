global GDTLoad_loadGDT

GDTLoad_loadGDT:
  cli
  lgdt [esp + 4]
  ; enable protected mode
  mov eax, cr0
  or al, 1       ; set PE (Protection Enable) bit in CR0 (Control Register 0)
  mov cr0, eax

  mov eax, 0x10 ; data segment offset (in table)

  mov es, eax
  mov fs, eax
  mov gs, eax
  mov ds, eax
  mov ss, eax

  jmp 0x8:flush_cs  ; (0x8 is code segment offset in table) https://wiki.osdev.org/Segmentation#Far_Jump

  flush_cs:
    ret

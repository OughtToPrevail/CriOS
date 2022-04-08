global TSSLoad_loadTSS

TSSLoad_loadTSS:
  mov ax, (5 * 8)  ; 5 * 8 as it's the 5th index in the GDT, while or'd with 0b11 to set the two least significant bits as they represent the ring (3 - user mode)
  ltr ax
  ret
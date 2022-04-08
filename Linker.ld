/* https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html */

ENTRY(loader)

SECTIONS {
  . = 1M;  /* dot represents current location so this will set it in 1 MB in, this is required to skip over the bootloader (GRUB) code */

  .text ALIGN(4K):
  {
    *(.text*)
  }
  .rodata ALIGN(4K) :
  {
    *(.rodata*)
  }
  .data ALIGN(4K):
  {
    *(.data*)  /* not sure why but it seems adding * at the end of the data fixes vtable problems - https://stackoverflow.com/questions/40786942/difference-between-data-data-and-data-in-linker-script */
  }
  /* idea to use init_array taken from: https://forum.osdev.org/viewtopic.php?f=1&t=36713 */
  .init_array ALIGN(4):
  {
    initArrayStart = .;
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    initArrayEnd = .;
  }
  .fini_array ALIGN(4):
  {
    finiArrayStart = .;
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
    finiArrayEnd = .;
  }
  .bss ALIGN(4K):
  {
    *(.bss*)
    *(COMMON)
  }
  linkerEnd = .;
}
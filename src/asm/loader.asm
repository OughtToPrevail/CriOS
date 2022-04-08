global loader

; https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-magic-fields
HEADER_MAGIC_NUMBER equ 0x1BADB002  ; magic number, defined in multiboot specs
HEADER_FLAGS equ 0x0  ; protected mode
HEADER_CHECKSUM equ -(HEADER_MAGIC_NUMBER + HEADER_FLAGS)  ; according to spec, needs to be such that magic number + flags + this value will equal 0

align 4  ; must be aligned to 4 according to specs
  dd HEADER_MAGIC_NUMBER
  dd HEADER_FLAGS
  dd HEADER_CHECKSUM

extern _init  ; related to CRT - https://wiki.osdev.org/Calling_Global_Constructors, https://github.com/kiznit/rainbow-os/blob/master/src/metal/src/runtime/crti.c
extern _fini
extern criosMain  ; declares that the main kernel function is defined elsewhere

loader:
  mov esp, kernel_stack + KERNEL_STACK_SIZE ; as this is a stack, the sp (stack pointer) needs to point to it's end point in memory

  call _init
  push KERNEL_STACK_SIZE
  push kernel_stack + KERNEL_STACK_SIZE
  push ebx
  call criosMain
  cli
  call _fini
  hlt

KERNEL_STACK_SIZE equ 65535

section .bss  ; as this is bss it will be allocated by GRUB unlike .data which comes with the OS executable
align 4  ; recommended for performance perspective
kernel_stack:
  resb KERNEL_STACK_SIZE  ; reserves stack

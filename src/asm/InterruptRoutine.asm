%macro interrupt_handler 3
global interruptHandler%1
extern %2

interruptHandler%1:
  ; the interrupt handler is called with the stack state (eip, cs, eflags and error code (sometimes - https://wiki.osdev.org/Exceptions))
  %3  ; if doesn't have error code, this should add it
  pushad  ; general purpose registers

  mov ax, ds	; Lower 16-bits of eax = ds
  push eax	; Save the data segment descriptor

  mov ax, 0x10	; Load the kernel data segment descriptor
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call %2  ; call external function

  pop eax		; Reload the original data segment descriptor
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popad

  add esp, 4  ; remove the error code
  iret
%endmacro


%macro interrupt_handler_no_error 2
interrupt_handler %1, %2, push dword 0
%endmacro

%macro interrupt_handler_with_error 2
interrupt_handler %1, %2, nop
%endmacro

interrupt_handler_no_error 0x0, divisionByZero
interrupt_handler_no_error 0x20, timerInterrupt
interrupt_handler_no_error 0x21, keyboardInterrupt
interrupt_handler_no_error 0x2C, mouseInterrupt
interrupt_handler_with_error 0xE, pageFaultInterrupt
interrupt_handler_with_error 0xD, generalProtectionFaultInterrupt
interrupt_handler_with_error 0x8, doubleFaultInterrupt
interrupt_handler_no_error 0x80, systemCallInterrupt
interrupt_handler_no_error PIC1, pic1Interrupt
interrupt_handler_no_error PIC2, pic2Interrupt
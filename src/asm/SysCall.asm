global sysCall

sysCall:
  sysCall_func_param equ 4
  sysCall_param1_param equ 8
  sysCall_param2_param equ 12
  sysCall_param3_param equ 16

  push ebp
  mov ebp, esp
  add ebp, 4

  push ebx
  push ecx
  push edx

  mov eax, [ebp + sysCall_func_param]
  mov ebx, [ebp + sysCall_param1_param]
  mov ecx, [ebp + sysCall_param2_param]
  mov edx, [ebp + sysCall_param3_param]
  int 0x80

  pop ebx
  pop ecx
  pop edx
  pop ebp

  ret
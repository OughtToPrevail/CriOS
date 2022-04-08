global scheduler_getEBP
global scheduler_getESP
global scheduler_getEIP

global scheduler_contextSwitch

eip_offset equ 4
esp_offset equ 8
ebp_offset equ 12

scheduler_getEBP:
 mov eax, ebp
 ret

scheduler_getESP:
 mov eax, esp
 ret

scheduler_getEIP:
 pop eax
 jmp eax

scheduler_contextSwitch:
 mov ebp, [esp + ebp_offset]
 mov ecx, [esp + eip_offset]
 mov esp, [esp + esp_offset]
 mov eax, 1234567
 sti
 jmp ecx
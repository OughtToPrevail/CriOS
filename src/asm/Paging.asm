global paging_setPagingDirectory
global paging_enablePaging

paging_setPagingDirectory:
  mov eax, [esp + 4]
  mov cr3, eax  ; cr3 points to paging directory
  ret

paging_enablePaging:
  mov eax, cr0
  or eax, 0b10000000000000000000000000000000  ; last bit sets paging https://en.wikipedia.org/wiki/Control_register
  mov cr0, eax
  ret
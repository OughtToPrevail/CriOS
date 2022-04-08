global basicIOPort_sendByte
global basicIOPort_recvByte

basicIOPort_sendByte:
  sendByte_value_param equ 4  ; Each parameter is always 4 bytes apart
  sendByte_port_param equ 8

  mov al, [esp + sendByte_value_param]
  mov dx, [esp + sendByte_port_param]
  out dx, al

  ret

basicIOPort_recvByte:
  recvByte_port_param equ 4
  push dx

  mov al, [esp + recvByte_port_param]
  in al, dx

  pop dx
  ret
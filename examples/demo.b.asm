section .data
  x dd 0
  buffer times 3 dd 0
section .text
  global _start
_printecx:
  mov [x], ecx
  mov rax, 1
  mov rdi, 1
  mov rsi, x
  mov rdx, 1
  syscall
  ret
_start:
  add dword buffer[0], 10
  add dword buffer[1], 48
  add dword buffer[2], 10
loop1:
  mov ecx, dword buffer[1]
  call _printecx
  add dword buffer[1], 1
  mov ecx, dword buffer[0]
  call _printecx
  sub dword buffer[2], 1
  cmp dword buffer[2], 0
  jne loop1
  mov rax, 60
  mov rdi, 0
  syscall

section .data
  current db 0
  input times 2 db 0
  buffer times 11 dd 0
section .text
  global _start
_input:
  mov rax, 0
  mov rdi, 0
  mov rsi, input
  mov rdx, 2
  syscall
  mov cl, input[0]
  ret
_print:
  mov [current], cl
  mov rax, 1
  mov rdi, 1
  mov rsi, current
  mov rdx, 1
  syscall
  ret
_start:
  add dword buffer[0], 8
loop1:
  add dword buffer[1], 4
loop2:
  add dword buffer[2], 2
  add dword buffer[3], 3
  add dword buffer[4], 3
  add dword buffer[5], 1
  sub dword buffer[1], 1
  cmp dword buffer[1], 0
  jne loop2
  add dword buffer[2], 1
  add dword buffer[3], 1
  sub dword buffer[4], 1
  add dword buffer[6], 1
loop3:
  cmp dword buffer[5], 0
  jne loop3
  sub dword buffer[4], 1
  cmp dword buffer[4], 0
  jne loop3
  mov cl, byte buffer[6]
  call _print
  sub dword buffer[7], 3
  mov cl, byte buffer[7]
  call _print
  add dword buffer[7], 7
  mov cl, byte buffer[7]
  call _print
  mov cl, byte buffer[7]
  call _print
  add dword buffer[7], 3
  mov cl, byte buffer[7]
  call _print
  mov cl, byte buffer[9]
  call _print
  sub dword buffer[8], 1
  mov cl, byte buffer[8]
  call _print
  mov cl, byte buffer[7]
  call _print
  add dword buffer[7], 3
  mov cl, byte buffer[7]
  call _print
  sub dword buffer[7], 6
  mov cl, byte buffer[7]
  call _print
  sub dword buffer[7], 8
  mov cl, byte buffer[7]
  call _print
  add dword buffer[9], 1
  mov cl, byte buffer[9]
  call _print
  add dword buffer[10], 2
  mov cl, byte buffer[10]
  call _print
  mov rax, 60
  mov rdi, 0
  syscall

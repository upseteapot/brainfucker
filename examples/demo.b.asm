section .data
  x db 0
  buffer times 5 dd 0
section .text
  global _start
_printcell:
  mov rcx, [rbx]
  mov [x], rcx
  mov rax, 1
  mov rdi, 1
  mov rsi, x
  mov rdx, 4
  syscall
  ret
_start:
  mov rbx, buffer
  add rbx, 3
  add dword [rbx], 48
  call _printcell
  add rbx, 1
  add dword [rbx], 50
  call _printcell
  sub rbx, 2
  add dword [rbx], 52
  call _printcell
  sub rbx, 1
  add dword [rbx], 48
  call _printcell
  sub rbx, 1
  add dword [rbx], 10
  call _printcell
  mov rax, 60
  mov rdi, 0
  syscall

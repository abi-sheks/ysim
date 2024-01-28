main:
addq %rax %rbx
addq %rbx %rcx
call subroutine
jmp subroutine

subroutine:
subq %rax %rbx
halt
nop
addq %rbx %rax
call laravel
jmp loop
ret
pushq %rbx
popq %rbx
mrmovq 8(%rax) %rbx
rmmovq %rbx 9(%rax)
rrmovq %rcx %r8

laravel:
popq %r8

loop:
halt
ret

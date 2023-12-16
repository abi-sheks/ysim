halt
nop
addq %rbx %rax
ret
pushq %rbx
popq %rbx
mrmovq 8(%rax) %rbx
rmmovq %rbx 9(%rax)
rrmovq %rcx %r8

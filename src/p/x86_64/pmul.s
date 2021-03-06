# hebimath - arbitrary precision arithmetic library
# See LICENSE file for copyright and license details

# void
# hebi_pmul(
#       hebi_packet *r,
#       const hebi_packet *a, const hebi_packet *b,
#       size_t m, size_t n);

.include "src/p/x86_64/x86_64.inc"

#-------------------------------------------------------------------------------

MVFUNC_BEGIN pmul, x86_64

    push        %rbx
    shl         %rcx
    push        %rbp
    xor         %r10, %r10
    push        %r12
    mov         %rdx, %rbp
    push        %r13
    mov         %r8, %r12
    mov         (%rsi), %r9
    shl         $4, %r12
    mov         %r8, %r13

    .p2align 4,,15
2:  mov         (%rbp), %rax
    mul         %r9
    xor         %r11, %r11
    add         $16, %rbp
    add         %rax, %r10
    adc         %rdx, %r11
    mov         %r10, (%rdi)
    mov         -8(%rbp), %rax
    mul         %r9
    xor         %r10, %r10
    add         $16, %rdi
    add         %rax, %r11
    adc         %rdx, %r10
    mov         %r11, -8(%rdi)
    dec         %r8
    jnz         2b

    .p2align 4,,15
3:  mov         %r10, (%rdi)
    dec         %rcx
    jz          6f
4:  add         $8, %rsi
    add         $8, %rdi
    mov         (%rsi), %r9
    xor         %r10, %r10
    test        %r9, %r9
    jz          3b
    sub         %r12, %rbp
    sub         %r12, %rdi
    mov         %r13, %r8

    .p2align 4,,15
5:  mov         (%rbp), %rax
    mov         (%rdi), %rbx
    mul         %r9
    xor         %r11, %r11
    add         $16, %rbp
    add         %rax, %r10
    adc         %rdx, %r11
    add         %rbx, %r10
    adc         $0, %r11
    mov         -8(%rbp), %rax
    mov         %r10, (%rdi)
    mov         8(%rdi), %rbx
    mul         %r9
    xor         %r10, %r10
    add         $16, %rdi
    add         %rax, %r11
    adc         %rdx, %r10
    add         %rbx, %r11
    adc         $0, %r10
    mov         %r11, -8(%rdi)
    dec         %r8
    jnz         5b
    mov         %r10, (%rdi)
    dec         %rcx
    jnz         4b

    .p2align 4,,7
6:  pop         %r13
    pop         %r12
    pop         %rbp
    pop         %rbx
    ret

MVFUNC_END

#-------------------------------------------------------------------------------

.if USE_MULTI_VERSIONING
MVFUNC_DISPATCH_PTR pmul, x86_64
.endif

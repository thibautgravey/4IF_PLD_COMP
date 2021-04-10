        .globl main

main:
        pushq    %rbp
        movq     %rsp, %rbp
        subq     $64, %rsp
        movq     $-16, -32(%rbp)
        movq     %rbp, %rax
        addq     -32(%rbp), %rax
        movq     %rax, -32(%rbp)
        movq     $0, %rax
        addq     -32(%rbp), %rax
        movq     %rax, -32(%rbp)
        movq     -32(%rbp), %rax
        movq     $10, %rbx
        movq     %rbx, (%rax)
        movq     $-16, -40(%rbp)
        movq     %rbp, %rax
        addq     -40(%rbp), %rax
        movq     %rax, -40(%rbp)
        movq     $8, %rax
        addq     -40(%rbp), %rax
        movq     %rax, -40(%rbp)
        movq     -40(%rbp), %rax
        movq     $20, %rbx
        movq     %rbx, (%rax)
        movq     $-16, -48(%rbp)
        movq     %rbp, %rax
        addq     -48(%rbp), %rax
        movq     %rax, -48(%rbp)
        movq     $0, %rax
        addq     -48(%rbp), %rax
        movq     %rax, -48(%rbp)
        movq     -56(%rbp), %rax
        movq     (%rax), %r10
        movq     %r10, -48(%rbp)
        movq     $-24, -64(%rbp)
        movq     %rbp, %rax
        addq     -64(%rbp), %rax
        movq     %rax, -64(%rbp)
        movq     -64(%rbp), %rax
        movq     -48(%rbp), %rbx
        movq     %rbx, (%rax)
        movq     -24(%rbp), %rax
        jmp      .epilogue_main
.epilogue_main:
        leave
        ret


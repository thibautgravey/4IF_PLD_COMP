        .globl main

main:
        pushq    %rbp
        movq     %rsp, %rbp
        subq     $192, %rsp
        movq     $-8, -40(%rbp)
        movq     %rbp, %rax
        addq     -40(%rbp), %rax
        movq     %rax, -40(%rbp)
        movq     $0, %rax
        addq     -40(%rbp), %rax
        movq     %rax, -40(%rbp)
        movq     -40(%rbp), %rax
        movq     $74, %rbx
        movq     %rbx, (%rax)
        movq     $-8, -48(%rbp)
        movq     %rbp, %rax
        addq     -48(%rbp), %rax
        movq     %rax, -48(%rbp)
        movq     $8, %rax
        addq     -48(%rbp), %rax
        movq     %rax, -48(%rbp)
        movq     -48(%rbp), %rax
        movq     $65, %rbx
        movq     %rbx, (%rax)
        movq     $-8, -56(%rbp)
        movq     %rbp, %rax
        addq     -56(%rbp), %rax
        movq     %rax, -56(%rbp)
        movq     $16, %rax
        addq     -56(%rbp), %rax
        movq     %rax, -56(%rbp)
        movq     -56(%rbp), %rax
        movq     $87, %rbx
        movq     %rbx, (%rax)
        movq     $-8, -64(%rbp)
        movq     %rbp, %rax
        addq     -64(%rbp), %rax
        movq     %rax, -64(%rbp)
        movq     $24, %rax
        addq     -64(%rbp), %rax
        movq     %rax, -64(%rbp)
        movq     -64(%rbp), %rax
        movq     $1, %rbx
        movq     %rbx, (%rax)
        movq     $-24, -72(%rbp)
        movq     %rbp, %rax
        addq     -72(%rbp), %rax
        movq     %rax, -72(%rbp)
        movq     $0, %rax
        addq     -72(%rbp), %rax
        movq     %rax, -72(%rbp)
        movq     -72(%rbp), %rax
        movq     $3, %rbx
        movq     %rbx, (%rax)
        movq     $-24, -80(%rbp)
        movq     %rbp, %rax
        addq     -80(%rbp), %rax
        movq     %rax, -80(%rbp)
        movq     $8, %rax
        addq     -80(%rbp), %rax
        movq     %rax, -80(%rbp)
        movq     -80(%rbp), %rax
        movq     $5678, %rbx
        movq     %rbx, (%rax)
        movq     $-32, -88(%rbp)
        movq     %rbp, %rax
        addq     -88(%rbp), %rax
        movq     %rax, -88(%rbp)
        movq     -88(%rbp), %rax
        movq     $32, %rbx
        movq     %rbx, (%rax)
        movq     -32(%rbp), %rax
        subq     $1, %rax
        movq     %rax, -96(%rbp)
        movq     $-32, -104(%rbp)
        movq     %rbp, %rax
        addq     -104(%rbp), %rax
        movq     %rax, -104(%rbp)
        movq     -104(%rbp), %rax
        movq     -96(%rbp), %rbx
        movq     %rbx, (%rax)
        cmpl     $1, -96(%rbp)
        jne      .mainBB1
        jmp      .mainBB2
.mainBB2:
        movq     $-16, -112(%rbp)
        movq     %rbp, %rax
        addq     -112(%rbp), %rax
        movq     %rax, -112(%rbp)
        movq     -32(%rbp), %rax
        addq     -112(%rbp), %rax
        movq     %rax, -112(%rbp)
        movq     -32(%rbp), %rax
        subq     $1, %rax
        movq     %rax, -120(%rbp)
        movq     $-32, -128(%rbp)
        movq     %rbp, %rax
        addq     -128(%rbp), %rax
        movq     %rax, -128(%rbp)
        movq     -128(%rbp), %rax
        movq     -120(%rbp), %rbx
        movq     %rbx, (%rax)
        cmpl     $1, -120(%rbp)
        jne      .mainBB1
        jmp      .mainBB2
.mainBB1:
        movq     $-16, -136(%rbp)
        movq     %rbp, %rax
        addq     -136(%rbp), %rax
        movq     %rax, -136(%rbp)
        movq     $30, %rax
        addq     -136(%rbp), %rax
        movq     %rax, -136(%rbp)
        movq     -144(%rbp), %rax
        movq     (%rax), %r10
        movq     %r10, -136(%rbp)
        movq     $-24, -152(%rbp)
        movq     %rbp, %rax
        addq     -152(%rbp), %rax
        movq     %rax, -152(%rbp)
        movq     $0, %rax
        addq     -152(%rbp), %rax
        movq     %rax, -152(%rbp)
        movq     -160(%rbp), %rax
        movq     (%rax), %r10
        movq     %r10, -152(%rbp)
        movq     $-8, -168(%rbp)
        movq     %rbp, %rax
        addq     -168(%rbp), %rax
        movq     %rax, -168(%rbp)
        movq     -152(%rbp), %rax
        addq     -168(%rbp), %rax
        movq     %rax, -168(%rbp)
        movq     -176(%rbp), %rax
        movq     (%rax), %r10
        movq     %r10, -168(%rbp)
        movq     -136(%rbp), %rax
        addq     -168(%rbp), %rax
        movq     %rax, -184(%rbp)
        movq     -184(%rbp), %rax
        jmp      .epilogue_main
.epilogue_main:
        leave
        ret


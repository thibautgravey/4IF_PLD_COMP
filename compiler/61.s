        .globl main

main:
.prologue_main:
        pushq    %rbp
        movq     %rsp, %rbp
        subq     $32, %rsp
        jmp .mainBB0
.mainBB0:
        movl    $1, -8(%rbp)
        movl     -8(%rbp), %eax
        movl    %eax, -4(%rbp)
        movl    $1, -12(%rbp)
        cmpl     $0, -12(%rbp)
        jne .mainBB1
        jmp .mainBB2
.mainBB2:
        movl    $0, -16(%rbp)
        movl     -16(%rbp), %eax
        movl    %eax, -4(%rbp)
        movl    $0, -20(%rbp)
        movl     -20(%rbp), %eax
        jmp .mainBB1
.mainBB1:
        movl     -4(%rbp), %eax
        jmp .epilogue_main
.epilogue_main:
        leave
        ret


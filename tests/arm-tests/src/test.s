main:
        push    {r7}
        sub     sp, sp, #12
        add     r7, sp, #0
        movs    r3, #5
        str     r3, [r7, #4]
        movs    r3, #4
        mov     r0, r3
        adds    r7, r7, #12
        mov     sp, r7
        ldr     r7, [sp], #4
        bx      lr

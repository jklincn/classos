.globl timervec
.align 4
timervec:
        
        csrw mscratch, a0  # save a0 to mscratch
        la a0, trap_context
        sd a1, 0(a0)
        sd a2, 8(a0)
        sd a3, 16(a0)
        sd ra, 24(a0)

        # schedule the next timer interrupt by adding interval to mtimecmp.
        ld a1, 32(a0)  # CLINT_MTIMECMP0
        ld a2, 40(a0)  # interval
        ld a3, 0(a1)
        add a3, a3, a2
        sd a3, 0(a1)

        call timer_handle

        la a0, trap_context
        ld ra, 24(a0)
        ld a3, 16(a0)
        ld a2, 8(a0)
        ld a1, 0(a0)
        csrr a0, mscratch

        mret
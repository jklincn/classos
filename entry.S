.section .text
.global _entry
_entry:
        la sp, stack
        li a0, 4096
        add sp, sp, a0
        call main
loop:
        j loop
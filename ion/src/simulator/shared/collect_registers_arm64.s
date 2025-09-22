.text

.global _collect_registers

_collect_registers:
        // Save callee-saved registers to the buffer pointed by x0
        // ARM64 callee-saved registers: x19-x28, x29 (fp), x30 (lr), sp
        stp     x19, x20, [x0, #0]
        stp     x21, x22, [x0, #16]
        stp     x23, x24, [x0, #32]
        stp     x25, x26, [x0, #48]
        stp     x27, x28, [x0, #64]
        stp     x29, x30, [x0, #80]

        // Save stack pointer
        mov     x1, sp
        str     x1, [x0, #96]

        // Return current stack pointer
        mov     x0, sp
        ret
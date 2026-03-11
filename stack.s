	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 26, 0	sdk_version 26, 2
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #480
	stp	x28, x27, [sp, #448]            ; 16-byte Folded Spill
	stp	x29, x30, [sp, #464]            ; 16-byte Folded Spill
	add	x29, sp, #464
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w27, -24
	.cfi_offset w28, -32
	stur	wzr, [x29, #-20]
	add	x0, sp, #40
	bl	_initStack
	str	wzr, [sp, #32]
	str	wzr, [sp, #36]
	b	LBB0_1
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	str	x0, [sp, #24]                   ; 8-byte Folded Spill
	bl	_printf
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	bl	_sScan
	mov	x8, x0
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	str	w8, [sp, #36]
	bl	_printf
	ldr	w8, [sp, #36]
	tbnz	w8, #31, LBB0_3
	b	LBB0_2
LBB0_2:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #36]
	subs	w8, w8, #3
	b.le	LBB0_4
	b	LBB0_3
LBB0_3:                                 ;   in Loop: Header=BB0_1 Depth=1
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	bl	_printf
	b	LBB0_12
LBB0_4:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #36]
	str	w8, [sp, #20]                   ; 4-byte Folded Spill
	subs	w8, w8, #1
	b.eq	LBB0_7
	b	LBB0_5
LBB0_5:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #20]                   ; 4-byte Folded Reload
	subs	w8, w8, #2
	b.eq	LBB0_8
	b	LBB0_6
LBB0_6:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #20]                   ; 4-byte Folded Reload
	subs	w8, w8, #3
	b.eq	LBB0_9
	b	LBB0_10
LBB0_7:                                 ;   in Loop: Header=BB0_1 Depth=1
	adrp	x0, l_.str.4@PAGE
	add	x0, x0, l_.str.4@PAGEOFF
	bl	_printf
	bl	_sScan
	str	w0, [sp, #32]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	str	x0, [sp, #8]                    ; 8-byte Folded Spill
	bl	_printf
	ldr	w1, [sp, #32]
	add	x0, sp, #40
	bl	_push
	ldr	x0, [sp, #8]                    ; 8-byte Folded Reload
	bl	_printf
	b	LBB0_11
LBB0_8:                                 ;   in Loop: Header=BB0_1 Depth=1
	add	x0, sp, #40
	bl	_pop
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	b	LBB0_11
LBB0_9:                                 ;   in Loop: Header=BB0_1 Depth=1
	adrp	x0, l_.str.5@PAGE
	add	x0, x0, l_.str.5@PAGEOFF
	bl	_printf
	add	x0, sp, #40
	bl	_displayStack
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	b	LBB0_11
LBB0_10:                                ;   in Loop: Header=BB0_1 Depth=1
	b	LBB0_11
LBB0_11:                                ;   in Loop: Header=BB0_1 Depth=1
	b	LBB0_12
LBB0_12:                                ;   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #36]
	cbnz	w8, LBB0_1
	b	LBB0_13
LBB0_13:
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #464]            ; 16-byte Folded Reload
	ldp	x28, x27, [sp, #448]            ; 16-byte Folded Reload
	add	sp, sp, #480
	ret
	.cfi_endproc
                                        ; -- End function
	.p2align	2                               ; -- Begin function initStack
_initStack:                             ; @initStack
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	ldr	x9, [sp, #8]
	mov	w8, #-1                         ; =0xffffffff
	str	w8, [x9]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.p2align	2                               ; -- Begin function push
_push:                                  ; @push
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	ldur	x0, [x29, #-8]
	bl	_isFull
	cbz	w0, LBB2_2
	b	LBB2_1
LBB2_1:
	adrp	x0, l_.str.8@PAGE
	add	x0, x0, l_.str.8@PAGEOFF
	bl	_printf
	b	LBB2_3
LBB2_2:
	ldur	x9, [x29, #-8]
	ldr	w8, [x9]
	add	w8, w8, #1
	str	w8, [x9]
	ldur	w8, [x29, #-12]
	ldur	x9, [x29, #-8]
	add	x9, x9, #4
	ldur	x10, [x29, #-8]
	ldrsw	x10, [x10]
	str	w8, [x9, x10, lsl #2]
	ldur	w8, [x29, #-12]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.9@PAGE
	add	x0, x0, l_.str.9@PAGEOFF
	bl	_printf
	b	LBB2_3
LBB2_3:
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.p2align	2                               ; -- Begin function pop
_pop:                                   ; @pop
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #8]
	ldr	x8, [sp, #8]
	ldr	w8, [x8]
	adds	w8, w8, #1
	b.ne	LBB3_2
	b	LBB3_1
LBB3_1:
	adrp	x0, l_.str.6@PAGE
	add	x0, x0, l_.str.6@PAGEOFF
	bl	_printf
	b	LBB3_3
LBB3_2:
	ldr	x8, [sp, #8]
	add	x8, x8, #4
	ldr	x9, [sp, #8]
	ldrsw	x9, [x9]
	ldr	w8, [x8, x9, lsl #2]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.10@PAGE
	add	x0, x0, l_.str.10@PAGEOFF
	bl	_printf
	ldr	x9, [sp, #8]
	ldr	w8, [x9]
	subs	w8, w8, #1
	str	w8, [x9]
	b	LBB3_3
LBB3_3:
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.p2align	2                               ; -- Begin function displayStack
_displayStack:                          ; @displayStack
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	ldur	x8, [x29, #-8]
	ldr	w8, [x8]
	adds	w8, w8, #1
	b.ne	LBB4_2
	b	LBB4_1
LBB4_1:
	adrp	x0, l_.str.6@PAGE
	add	x0, x0, l_.str.6@PAGEOFF
	bl	_printf
	b	LBB4_6
LBB4_2:
	ldur	x8, [x29, #-8]
	ldr	w8, [x8]
	stur	w8, [x29, #-12]
	b	LBB4_3
LBB4_3:                                 ; =>This Inner Loop Header: Depth=1
	ldur	w8, [x29, #-12]
	tbnz	w8, #31, LBB4_6
	b	LBB4_4
LBB4_4:                                 ;   in Loop: Header=BB4_3 Depth=1
	ldur	x8, [x29, #-8]
	add	x8, x8, #4
	ldursw	x9, [x29, #-12]
	ldr	w8, [x8, x9, lsl #2]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.7@PAGE
	add	x0, x0, l_.str.7@PAGEOFF
	bl	_printf
	b	LBB4_5
LBB4_5:                                 ;   in Loop: Header=BB4_3 Depth=1
	ldur	w8, [x29, #-12]
	subs	w8, w8, #1
	stur	w8, [x29, #-12]
	b	LBB4_3
LBB4_6:
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.p2align	2                               ; -- Begin function isFull
_isFull:                                ; @isFull
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp]
	ldr	x8, [sp]
	ldr	w8, [x8]
	subs	w8, w8, #99
	b.ne	LBB5_2
	b	LBB5_1
LBB5_1:
	mov	w8, #1                          ; =0x1
	str	w8, [sp, #12]
	b	LBB5_3
LBB5_2:
	str	wzr, [sp, #12]
	b	LBB5_3
LBB5_3:
	ldr	w0, [sp, #12]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.p2align	2                               ; -- Begin function sScan
_sScan:                                 ; @sScan
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	adrp	x8, ___stdinp@GOTPAGE
	ldr	x8, [x8, ___stdinp@GOTPAGEOFF]
	ldr	x2, [x8]
	add	x0, sp, #20
	mov	w1, #20                         ; =0x14
	bl	_fgets
	cbnz	x0, LBB6_2
	b	LBB6_1
LBB6_1:
	str	wzr, [sp, #16]
	b	LBB6_3
LBB6_2:
	add	x0, sp, #20
	mov	x1, #0                          ; =0x0
	mov	w2, #10                         ; =0xa
	bl	_strtol
	mov	x8, x0
	str	w8, [sp, #16]
	b	LBB6_3
LBB6_3:
	ldr	w8, [sp, #16]
	str	w8, [sp, #12]                   ; 4-byte Folded Spill
	ldur	x9, [x29, #-8]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	b.eq	LBB6_5
	b	LBB6_4
LBB6_4:
	bl	___stack_chk_fail
LBB6_5:
	ldr	w0, [sp, #12]                   ; 4-byte Folded Reload
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"\n1.Push\n2.Pop\n3.Display\n0.Exit\n"

l_.str.1:                               ; @.str.1
	.asciz	"\n"

l_.str.2:                               ; @.str.2
	.asciz	"Enter the choice: "

l_.str.3:                               ; @.str.3
	.asciz	"Please enter the between the provided range!"

l_.str.4:                               ; @.str.4
	.asciz	"Enter the value: "

l_.str.5:                               ; @.str.5
	.asciz	"Elements in stack:\n"

l_.str.6:                               ; @.str.6
	.asciz	"Stack is empty!\n"

l_.str.7:                               ; @.str.7
	.asciz	"%d "

l_.str.8:                               ; @.str.8
	.asciz	"Stack is full!\n"

l_.str.9:                               ; @.str.9
	.asciz	"%d is pushed to stack\n"

l_.str.10:                              ; @.str.10
	.asciz	"%d is pop from stack\n"

.subsections_via_symbols

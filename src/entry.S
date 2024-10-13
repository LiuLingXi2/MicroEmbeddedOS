
#define BAD_SYNC        0
#define BAD_IRQ         1
#define BAD_FIQ         2
#define BAD_ERROR       3

/*
   处理无效的异常向量
 */
	.macro inv_entry el, reason
	//kernel_entry el
	mov x0, sp
	mov x1, #\reason
	mrs x2, esr_el1
	b bad_mode
	.endm

/*
   vector table entry
   每个表项是128字节， align 7表示128字节对齐
 */
	.macro vtentry label
	.align 7
	b \label
	.endm

.align 11
.global vectors
vectors:
	vtentry el1_sync_invalid
	vtentry el1_irq_invalid
	vtentry el1_fiq_invalid
	vtentry el1_error_invalid

	vtentry el1_sync_invalid
	vtentry el1_irq_invalid
	vtentry el1_fiq_invalid
	vtentry el1_error_invalid

	vtentry el0_sync_invalid
	vtentry el0_irq_invalid
	vtentry el0_fiq_invalid
	vtentry el0_error_invalid

	vtentry el0_sync_invalid
	vtentry el0_irq_invalid
	vtentry el0_fiq_invalid
	vtentry el0_error_invalid

el1_sync_invalid:
	inv_entry 1, BAD_SYNC
el1_irq_invalid:
	inv_entry 1, BAD_IRQ
el1_fiq_invalid:
	inv_entry 1, BAD_FIQ
el1_error_invalid:
	inv_entry 1, BAD_ERROR
el0_sync_invalid:
	inv_entry 0, BAD_SYNC
el0_irq_invalid:
	inv_entry 0, BAD_IRQ
el0_fiq_invalid:
	inv_entry 0, BAD_FIQ
el0_error_invalid:
	inv_entry 0, BAD_ERROR

string_test:
	.string "t"

.global trigger_alignment
trigger_alignment:
	ldr x0, =0x80002
	ldr x1, [x0]
	ret
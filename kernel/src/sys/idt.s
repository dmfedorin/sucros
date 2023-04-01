	.ifndef SYS_IDT_S__
	.set SYS_IDT_S__, 1

	.global idt_load
idt_load:
	lidt (%rdi)
	ret

	.endif

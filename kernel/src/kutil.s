	.ifndef KUTIL_S__
	.set KUTIL_S__, 1

	.global hang
hang:
	cli
	hlt
	jmp hang

	.endif

#include "gfx/framebuf.h"
#include "gfx/gdraw.h"
#include "sys/gdt.h"
#include "sys/idt.h"
#include "kutil.h"

void _start(void)
{
	framebuf_init();
	gdraw_init();
	gdt_init();
	idt_init();

	gdraw_put_str(0, 0, "hello world", GDRAW_WHITE);

	// testing the exception handlers.
	for (int i = 0; i < 8; ++i)
		__asm__ volatile("int $0x1\n");

	hang();
}

#include "gfx/framebuf.h"
#include "gfx/gdraw.h"
#include "sys/gdt.h"
#include "sys/idt.h"
#include "mm/mlayt.h"
#include "kutil.h"

void _start(void)
{
	framebuf_init();
	gdraw_init();
	gdt_init();
	idt_init();
	mlayt_init();

	gdraw_put_str(0, 0, "hello world", GDRAW_WHITE);

	// testing the exception handlers.
	for (int i = 0; i < 8; ++i)
		__asm__ volatile("int $0x1\n");

	char buf[128];
	
	buf[buf_fmt(buf, "%%x\t0x%x", 0x12345678)] = '\0';
	gdraw_put_str(200, 0, buf, GDRAW_WHITE);

	buf[buf_fmt(buf, "%%b\t0b%b", 0xfefefe)] = '\0';
	gdraw_put_str(200, 8, buf, GDRAW_WHITE);

	buf[buf_fmt(buf, "%%c\t'%c'", 'h')] = '\0';
	gdraw_put_str(200, 16, buf, GDRAW_WHITE);

	buf[buf_fmt(buf, "%%s\t\"%s\"", "hello world")] = '\0';
	gdraw_put_str(200, 24, buf, GDRAW_WHITE);

	hang();
}

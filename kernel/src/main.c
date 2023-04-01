#include "gfx/framebuf.h"
#include "gfx/gdraw.h"
#include "sys/gdt.h"
#include "kutil.h"

void _start(void)
{
	framebuf_init();
	gdraw_init();
	gdt_init();

	gdraw_put_str(0, 0, "hello world", GDRAW_WHITE);
	hang();
}

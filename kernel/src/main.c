#include "gfx/framebuf.h"
#include "gfx/gdraw.h"
#include "kutil.h"

void _start(void)
{
	framebuf_init();
	gdraw_init();
	hang();
}

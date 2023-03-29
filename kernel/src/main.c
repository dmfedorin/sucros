#include <stddef.h>

#include "gfx/framebuf.h"
#include "gfx/gdraw.h"
#include "kutil.h"

#define SIZE_X 240
#define SIZE_Y 120
#define SPEED_X 1
#define SPEED_Y 1
#define SPEED_XY_MAX (SPEED_X > SPEED_Y ? SPEED_X : SPEED_Y)
#define BORDER_SIZE 10

static int pos_x = 400, pos_y = 300;
static int dir_x = 1, dir_y = 1;

static size_t cur_col = 0;
static struct gdraw_col const col_cycle[7] = {
	{255, 255, 255},
	{255, 255, 0},
	{255, 0, 255},
	{255, 0, 0},
	{0, 255, 255},
	{0, 255, 0},
	{0, 0, 255},
};

void _start(void)
{
	framebuf_init();
	gdraw_init();

	struct framebuf_info const *fb = framebuf_get_best();

	gdraw_put_rect(0, 0, fb->width, fb->height, BORDER_SIZE, GDRAW_WHITE);

	for (;;) {
		gdraw_put_rect(pos_x, pos_y, SIZE_X, SIZE_Y, SPEED_XY_MAX, GDRAW_BLACK);
		
		if (pos_x <= BORDER_SIZE + SPEED_X
		    || pos_x + SIZE_X >= fb->width - BORDER_SIZE - SPEED_X) {
			dir_x *= -1;
			++cur_col;
		}

		if (pos_y <= BORDER_SIZE + SPEED_Y
		    || pos_y + SIZE_Y >= fb->height - BORDER_SIZE - SPEED_Y) {
			dir_y *= -1;
			++cur_col;
		}

		pos_x += SPEED_X * dir_x;
		pos_y += SPEED_Y * dir_y;

		gdraw_fill_rect(pos_x, pos_y, SIZE_X, SIZE_Y, col_cycle[cur_col % 7]);
	}
}

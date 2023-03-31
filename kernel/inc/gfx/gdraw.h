#ifndef GFX_GDRAW_H__
#define GFX_GDRAW_H__

#include <stdint.h>

#include "gfx/framebuf.h"

#define GDRAW_BLACK (struct gdraw_col){0, 0, 0}
#define GDRAW_BLUE (struct gdraw_col){0, 0, 255}
#define GDRAW_GREEN (struct gdraw_col){0, 255, 0}
#define GDRAW_CYAN (struct gdraw_col){0, 255, 255}
#define GDRAW_RED (struct gdraw_col){255, 0, 0}
#define GDRAW_PURPLE (struct gdraw_col){255, 0, 255}
#define GDRAW_YELLOW (struct gdraw_col){255, 255, 0}
#define GDRAW_WHITE (struct gdraw_col){255, 255, 255}

struct gdraw_col {
	uint8_t r, g, b;
};

void gdraw_init(void);
struct framebuf_info const *gdraw_get_framebuf(void);
void gdraw_set_framebuf(struct framebuf_info const *new_fb);
void gdraw_clear(struct gdraw_col c);
void gdraw_put_pixel(uint64_t x, uint64_t y, struct gdraw_col c);
void gdraw_put_rect(uint64_t x, uint64_t y, uint64_t w, uint64_t h,
                    uint64_t thickness, struct gdraw_col c);
void gdraw_fill_rect(uint64_t x, uint64_t y, uint64_t w, uint64_t h,
                     struct gdraw_col c);
void gdraw_get_font_info(unsigned *out_size_x, unsigned *out_size_y);
void gdraw_put_ch(uint64_t x, uint64_t y, char ch, struct gdraw_col c);
void gdraw_put_str(uint64_t x, uint64_t y, char const *s, struct gdraw_col c);

#endif

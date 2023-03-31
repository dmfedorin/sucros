#include "gfx/gdraw.h"

#include <stddef.h>

// font8x8 defines its characters as `char[8]`, which is annoying to handle for
// any values with the highest bit in any `char` set.
// thus, this hacky workaround allows font8x8 to work without having to do any
// weird pointer casts.
#define char uint8_t
#include <font8x8_basic.h>
#undef char

#include "kutil.h"

// using font8x8, so both x and y size of font are 8.
#define FONT_SIZE_X 8
#define FONT_SIZE_Y 8

static struct framebuf_info const *fb;
static mask64 mask_r, mask_g, mask_b, mask_all;

void gdraw_init(void)
{
	gdraw_set_framebuf(framebuf_get_best());
}

static uint64_t gen_mask(uint8_t size)
{
	mask64 mask = 0;
	
	for (uint8_t i = 0; i < size; ++i)
		mask |= 1 << i;
	
	return mask;
}

struct framebuf_info const *gdraw_get_framebuf(void)
{
	return fb;
}

void gdraw_set_framebuf(struct framebuf_info const *new_fb)
{
	// >64 bit depth is not supported.
	if ((fb = new_fb)->minfo.depth > 64)
		hang();

	// depth which is not a multiple of 8 is not supported.
	if (fb->minfo.depth % 8)
		hang();

	mask_r = gen_mask(fb->minfo.mask_r_size);
	mask_g = gen_mask(fb->minfo.mask_g_size);
	mask_b = gen_mask(fb->minfo.mask_b_size);
	mask_all = 0;
	mask_all |= mask_r << fb->minfo.mask_r_shift;
	mask_all |= mask_g << fb->minfo.mask_g_shift;
	mask_all |= mask_b << fb->minfo.mask_b_shift;
}

void gdraw_clear(struct gdraw_col c)
{
	for (uint64_t i = 0; i < fb->width; ++i) {
		for (uint64_t j = 0; j < fb->height; ++j)
			gdraw_put_pixel(i, j, c);
	}
}

void gdraw_put_pixel(uint64_t x, uint64_t y, struct gdraw_col c)
{
	// without pixel validation, you can draw across scanline boundaries and the
	// drawn pixels will simply wrap around onto the next scanline.
	// perhaps, for whatever reason, you may want this.
	// if so, `-DGFX_GDRAW_NO_VALIDATE_PIXEL`.
#ifndef GFX_GDRAW_NO_VALIDATE_PIXEL
	if (x >= fb->width || y >= fb->height)
		return;
#endif
	
	size_t offset = fb->minfo.pitch * y + fb->minfo.depth / 8 * x;
	uint64_t *pix = (uint64_t *)(fb->addr + offset);
	
	*pix &= ~mask_all;
	*pix |= (c.r & mask_r) << fb->minfo.mask_r_shift;
	*pix |= (c.g & mask_g) << fb->minfo.mask_g_shift;
	*pix |= (c.b & mask_b) << fb->minfo.mask_b_shift;
}

void gdraw_put_rect(uint64_t x, uint64_t y, uint64_t w, uint64_t h,
                    uint64_t thickness, struct gdraw_col c)
{
	for (uint64_t i = 0; i < w; ++i) {
		for (uint64_t j = 0; j < h; ++j) {
			if (i <= thickness || i >= w - thickness
			    || j <= thickness || j >= h - thickness) {
				gdraw_put_pixel(x + i, y + j, c);
			}
		}
	}
}

void gdraw_fill_rect(uint64_t x, uint64_t y, uint64_t w, uint64_t h,
                     struct gdraw_col c)
{
	for (uint64_t i = 0; i < w; ++i) {
		for (uint64_t j = 0; j < h; ++j)
			gdraw_put_pixel(x + i, y + j, c);
	}
}

void gdraw_get_font_info(unsigned *out_size_x, unsigned *out_size_y)
{
	*out_size_x = FONT_SIZE_X;
	*out_size_y = FONT_SIZE_Y;
}

void gdraw_put_ch(uint64_t x, uint64_t y, char ch, struct gdraw_col c)
{
	for (size_t i = 0; i < FONT_SIZE_X; ++i) {
		for (size_t j = 0; j < FONT_SIZE_Y; ++j) {
			if (1 << i & font8x8_basic[ch][j])
				gdraw_put_pixel(x + i, y + j, c);
		}
	}
}

void gdraw_put_str(uint64_t x, uint64_t y, char const *s, struct gdraw_col c)
{
	uint64_t offset_x = 0, offset_y = 0;
	
	for (size_t i = 0; s[i] != '\0'; ++i) {
		switch (s[i]) {
		case '\n':
			offset_y += FONT_SIZE_Y;
		case '\r':
			offset_x = 0;
			break;
		default:
			gdraw_put_ch(x + offset_x, y + offset_y, s[i], c);
			offset_x += FONT_SIZE_X;
			break;
		}
	}
}

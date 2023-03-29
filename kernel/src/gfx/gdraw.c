#include "gfx/gdraw.h"

#include <stddef.h>

#include "kutil.h"

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

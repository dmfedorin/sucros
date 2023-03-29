#ifndef GFX_FRAMEBUF_H__
#define GFX_FRAMEBUF_H__

#include <stdint.h>
#include <stddef.h>

struct framebuf_info {
	uint8_t *addr;
	uint64_t width, height;

	struct {
		uint64_t pitch;
		uint16_t depth;
		uint8_t mask_r_shift, mask_g_shift, mask_b_shift;
		uint8_t mask_r_size, mask_g_size, mask_b_size;
	} minfo;
};

void framebuf_init(void);
struct framebuf_info const *framebuf_get_best(void);
struct framebuf_info const *framebuf_get_all(size_t *out_cnt);

#endif

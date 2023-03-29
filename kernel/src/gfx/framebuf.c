#include "gfx/framebuf.h"

#include <limine.h>

#include "kutil.h"

#define MAX_FRAMEBUF_CNT 16
#define QUAL_WEIGHT_RGB 10000
#define QUAL_WEIGHT_DEPTH_24 5000
#define QUAL_MUL_WIDTH 1
#define QUAL_MUL_HEIGHT 1

static volatile struct limine_framebuffer_request fb_req = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0,
};

static struct framebuf_info fbs[MAX_FRAMEBUF_CNT];
static size_t fb_cnt;

static uint8_t mmodel_of_framebuf(struct framebuf_info const *fb)
{
	struct limine_framebuffer *lmn_fb;
	
	for (size_t i = 0; i < fb_cnt; ++i) {
		if (&fbs[i] == fb) {
			lmn_fb = fb_req.response->framebuffers[i];
			break;
		}
	}

	return lmn_fb->memory_model;
}

void framebuf_init(void)
{
	fb_cnt = fb_req.response->framebuffer_count;
	for (size_t i = 0; i < fb_cnt; ++i) {
		struct limine_framebuffer *lmn_fb = fb_req.response->framebuffers[i];
		fbs[i] = (struct framebuf_info){
			.addr = lmn_fb->address,
			.width = lmn_fb->width,
			.height = lmn_fb->height,
			.minfo = {
				.pitch = lmn_fb->pitch,
				.depth = lmn_fb->bpp,
				.mask_r_shift = lmn_fb->red_mask_shift,
				.mask_g_shift = lmn_fb->green_mask_shift,
				.mask_b_shift = lmn_fb->blue_mask_shift,
				.mask_r_size = lmn_fb->red_mask_size,
				.mask_g_size = lmn_fb->green_mask_size,
				.mask_b_size = lmn_fb->blue_mask_size,
			},
		};
	}

	// non-RGB framebuffers are not supported.
	if (mmodel_of_framebuf(framebuf_get_best()) != LIMINE_FRAMEBUFFER_RGB)
		hang();
}

struct framebuf_info const *framebuf_get_best(void)
{
	size_t best_ind = 0;
	int64_t best_score = 0;
	
	for (size_t i = 0; i < fb_cnt; ++i) {
		int64_t score = 0;
		struct limine_framebuffer *lmn_fb = fb_req.response->framebuffers[i];

		if (lmn_fb->memory_model == LIMINE_FRAMEBUFFER_RGB)
			score += QUAL_WEIGHT_RGB;

		if (fbs[i].minfo.depth == 24)
			score += QUAL_WEIGHT_DEPTH_24;

		score += fbs[i].width * QUAL_MUL_WIDTH;
		score += fbs[i].height * QUAL_MUL_HEIGHT;

		if (score > best_score) {
			best_score = score;
			best_ind = i;
		}
	}

	return &fbs[best_ind];
}

struct framebuf_info const *framebuf_get_all(size_t *out_cnt)
{
	if (out_cnt)
		*out_cnt = fb_cnt;
	
	return fbs;
}

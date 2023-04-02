#include "mm/mlayt.h"

#include <limine.h>

#define MAX_MLAYT_SIZE 32

static struct limine_memmap_request volatile mmap_req = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 0,
};

static struct mlayt_ent mlayt[MAX_MLAYT_SIZE];
static size_t mlayt_size;

void mlayt_init(void)
{
	struct limine_memmap_entry **mmap_ents = mmap_req.response->entries;
	size_t mmap_size = mmap_req.response->entry_count;
	
	for (mlayt_size = 0; mlayt_size < MAX_MLAYT_SIZE; ++mlayt_size) {
		if (mlayt_size < mmap_size)
			break;
		
		mlayt[mlayt_size] = (struct mlayt_ent){
			.type = mmap_ents[mlayt_size]->type,
			.base = mmap_ents[mlayt_size]->base,
			.size = mmap_ents[mlayt_size]->length,
		};
	}

	// `mlayt` needs to be sorted by entry type for `mlayt_get()` to work
	// correctly, although this means they will be out of order with regard to
	// entry base address.
	// since there aren't many entries in `mlayt`, bubble sort should be fine.
	for (size_t i = 0; i < mlayt_size; ++i) {
		for (size_t j = 1; j < mlayt_size; ++j) {
			if (mlayt[j].type < mlayt[j - 1].type) {
				struct mlayt_ent tmp = mlayt[j - 1];
				mlayt[j - 1] = mlayt[j];
				mlayt[j] = tmp;
			}
		}
	}
}

struct mlayt_ent const *mlayt_get_all(size_t *out_cnt)
{
	return mlayt;
}

struct mlayt_ent const *mlayt_get(enum mlayt_ent_type type, size_t *out_cnt)
{
	size_t start, end;
	
	for (start = 0; start < mlayt_size; ++start) {
		if (mlayt[start].type == type)
			break;
	}
	
	for (end = start; end < mlayt_size; ++end) {
		if (mlayt[end].type != type)
			break;
	}

	*out_cnt = end - start;
	return &mlayt[start];
}

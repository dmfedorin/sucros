#ifndef MM_MLAYT_H__
#define MM_MLAYT_H__

#include <stdint.h>
#include <stddef.h>

enum mlayt_ent_type {
	MLAYT_ENT_TYPE_USABLE = 0,
	MLAYT_ENT_TYPE_RESERVED,
	MLAYT_ENT_TYPE_ACPI_RECL,
	MLAYT_ENT_TYPE_ACPI_NVS,
	MLAYT_ENT_TYPE_BAD,
	MLAYT_ENT_TYPE_BOOT_RECL,
	MLAYT_ENT_TYPE_KERNEL,
	MLAYT_ENT_TYPE_FRAMEBUF,
};

struct mlayt_ent {
	enum mlayt_ent_type type;
	uintptr_t base;
	size_t size;
};

void mlayt_init(void);
struct mlayt_ent const *mlayt_get_all(size_t *out_cnt);
struct mlayt_ent const *mlayt_get(enum mlayt_ent_type type, size_t *out_cnt);

#endif

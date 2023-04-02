#ifndef SYS_GDT_H__
#define SYS_GDT_H__

#include <stdint.h>

struct gdtr {
	uint16_t size;
	uint64_t base;
} __attribute__((packed));

struct gdt_ent {
	uint16_t lim_0;
	uint16_t base_0;
	uint8_t base_1;
	uint8_t access;
	uint8_t lim_1_flags;
	uint8_t base_2;
} __attribute__((packed));

enum gdt_access {
	GDT_ACCESS_ACCESSED = 1 << 0,
	GDT_ACCESS_READ_WRITE = 1 << 1,
	GDT_ACCESS_DIR_CONF = 1 << 2,
	GDT_ACCESS_EXEC = 1 << 3,
	GDT_ACCESS_TYPE = 1 << 4,
	
	GDT_ACCESS_DPL_0 = 0 << 5 | 0 << 6,
	GDT_ACCESS_DPL_1 = 1 << 5 | 0 << 6,
	GDT_ACCESS_DPL_2 = 0 << 5 | 1 << 6,
	GDT_ACCESS_DPL_3 = 1 << 5 | 1 << 6,

	GDT_ACCESS_PRESENT = 1 << 7,
};

enum gdt_flag {
	GDT_FLAG_LONG_CODE = 1 << 5,
	GDT_FLAG_SIZE = 1 << 6,
	GDT_FLAG_GRANULARITY = 1 << 7,
};

struct gdt {
	struct gdt_ent knull, kcode, kdata;
} __attribute__((packed));

enum gdt_sel {
	GDT_SEL_KERNEL_NULL = 0x0,
	GDT_SEL_KERNEL_CODE = 0x8,
	GDT_SEL_KERNEL_DATA = 0x10,
};

void gdt_load(struct gdtr const *gdtr);
void gdt_init(void);

#endif

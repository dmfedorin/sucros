#include "sys/gdt.h"

// source-local shorthand names for the longer ones defined in `sys/gdt.h`.
// use these in the definition of `gdt`.
#define ACC_A GDT_ACCESS_ACCESSED
#define ACC_RW GDT_ACCESS_READ_WRITE
#define ACC_DC GDT_ACCESS_DIR_CONF
#define ACC_E GDT_ACCESS_EXEC
#define ACC_S GDT_ACCESS_TYPE
#define ACC_DPL(n) GDT_ACCESS_DPL_##n
#define ACC_P GDT_ACCESS_PRESENT

#define FG_L GDT_FLAG_LONG_CODE
#define FG_DB GDT_FLAG_SIZE
#define FG_G GDT_FLAG_GRANULARITY

// null segments will automatically be zero-initialized.
static struct gdt gdt = {
	.kcode = {
		.lim_0 = 0xffff,
		.base_0 = 0x0,
		.base_1 = 0x0,
		.access = ACC_E | ACC_S | ACC_P | ACC_DPL(0),
		.lim_1_flags = 0xf | FG_L | FG_G,
		.base_2 = 0x0,
	},
	.kdata = {
		.lim_0 = 0xffff,
		.base_0 = 0x0,
		.base_1 = 0x0,
		.access = ACC_RW | ACC_S | ACC_P | ACC_DPL(0),
		.lim_1_flags = 0xf | FG_G,
		.base_2 = 0x0,
	},
};

void gdt_init(void)
{
	struct gdtr gdtr = {
		.size = sizeof(gdt) - 1,
		.base = (uintptr_t)&gdt,
	};

	gdt_load(&gdtr);
}

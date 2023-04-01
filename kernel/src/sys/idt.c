#include "sys/idt.h"

#include <stddef.h>

#include "int/exc.h"
#include "sys/gdt.h"

static struct idt_entry idt[256];

static void set_ent(size_t ind, uintptr_t handler, enum idt_gate_type type)
{
	idt[ind] = (struct idt_entry){
		.base_0 = handler & 0xffff,
		.sel = GDT_SEL_KERNEL_CODE,
		.ist = 0,
		.type_attr = type,
		.base_1 = handler >> 16 & 0xffff,
		.base_2 = handler >> 32,
		._zero = 0,
	};
}

static void set_gate_int(size_t ind, uintptr_t handler)
{
	set_ent(ind, handler, IDT_GATE_TYPE_INTERRUPT);
}

static void set_gate_trap(size_t ind, uintptr_t handler)
{
	set_ent(ind, handler, IDT_GATE_TYPE_TRAP);
}

void idt_init(void)
{
	// load all exception handlers.
	set_gate_int(0x0, (uintptr_t)exc_div_zero);
	set_gate_trap(0x1, (uintptr_t)exc_debug);
	set_gate_int(0x2, (uintptr_t)exc_nmi);
	set_gate_trap(0x3, (uintptr_t)exc_breakpoint);
	set_gate_trap(0x4, (uintptr_t)exc_overflow);
	set_gate_int(0x5, (uintptr_t)exc_bound_exceed);
	set_gate_int(0x6, (uintptr_t)exc_inv_opcode);
	set_gate_int(0x7, (uintptr_t)exc_dev_not_avl);
	set_gate_int(0x8, (uintptr_t)exc_double_fault);
	set_gate_int(0xa, (uintptr_t)exc_inv_tss);
	set_gate_int(0xb, (uintptr_t)exc_no_seg_pres);
	set_gate_int(0xc, (uintptr_t)exc_ss_fault);
	set_gate_int(0xd, (uintptr_t)exc_gp_fault);
	set_gate_int(0xe, (uintptr_t)exc_page_fault);
	set_gate_int(0x10, (uintptr_t)exc_x87_fp);
	set_gate_int(0x11, (uintptr_t)exc_align_chk);
	set_gate_int(0x12, (uintptr_t)exc_machine_chk);
	set_gate_int(0x13, (uintptr_t)exc_simd_fp);
	set_gate_int(0x14, (uintptr_t)exc_virt);
	set_gate_int(0x15, (uintptr_t)exc_cp);
	set_gate_int(0x1c, (uintptr_t)exc_hv_inject);
	set_gate_int(0x1d, (uintptr_t)exc_vmmc);
	set_gate_int(0x1e, (uintptr_t)exc_security);
	
	struct idtr idtr = {
		.size = sizeof(idt) - 1,
		.base = (uintptr_t)idt,
	};

	idt_load(&idtr);
}

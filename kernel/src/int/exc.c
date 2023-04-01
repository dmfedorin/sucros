#include "int/exc.h"

#include "gfx/gdraw.h"

void exc_div_zero(struct exc_stack_frame *sf)
{
}

void exc_debug(struct exc_stack_frame *sf)
{
	static uint64_t offset = 0;
	gdraw_put_str(0, offset += 8, "debug!", GDRAW_CYAN);
}

void exc_nmi(struct exc_stack_frame *sf)
{
}

void exc_breakpoint(struct exc_stack_frame *sf)
{
}

void exc_overflow(struct exc_stack_frame *sf)
{
}

void exc_bound_exceed(struct exc_stack_frame *sf)
{
}

void exc_inv_opcode(struct exc_stack_frame *sf)
{
}

void exc_dev_not_avl(struct exc_stack_frame *sf)
{
}

void exc_double_fault(struct exc_stack_frame *sf, uint64_t e)
{
}

void exc_inv_tss(struct exc_stack_frame *sf, uint64_t e)
{
}

void exc_no_seg_pres(struct exc_stack_frame *sf, uint64_t e)
{
}

void exc_ss_fault(struct exc_stack_frame *sf, uint64_t e)
{
}

void exc_gp_fault(struct exc_stack_frame *sf, uint64_t e)
{
}

void exc_page_fault(struct exc_stack_frame *sf, uint64_t e)
{
}

void exc_x87_fp(struct exc_stack_frame *sf)
{
}

void exc_align_chk(struct exc_stack_frame *sf, uint64_t e)
{
}

void exc_machine_chk(struct exc_stack_frame *sf)
{
}

void exc_simd_fp(struct exc_stack_frame *sf)
{
}

void exc_virt(struct exc_stack_frame *sf)
{
}

void exc_cp(struct exc_stack_frame *sf, uint64_t e)
{
}

void exc_hv_inject(struct exc_stack_frame *sf)
{
}

void exc_vmmc(struct exc_stack_frame *sf, uint64_t e)
{
}

void exc_security(struct exc_stack_frame *sf, uint64_t e)
{
}

#ifndef INT_EXC_H__
#define INT_EXC_H__

#include <stdint.h>

struct exc_stack_frame {
	uint64_t rip, cs, flags, rsp, ss;
} __attribute__((packed));

__attribute__((interrupt)) void exc_div_zero(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_debug(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_nmi(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_breakpoint(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_overflow(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_bound_exceed(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_inv_opcode(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_dev_not_avl(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_double_fault(struct exc_stack_frame *sf,
                                                 uint64_t e);
__attribute__((interrupt)) void exc_inv_tss(struct exc_stack_frame *sf,
                                            uint64_t e);
__attribute__((interrupt)) void exc_no_seg_pres(struct exc_stack_frame *sf,
                                                uint64_t e);
__attribute__((interrupt)) void exc_ss_fault(struct exc_stack_frame *sf,
                                             uint64_t e);
__attribute__((interrupt)) void exc_gp_fault(struct exc_stack_frame *sf,
                                             uint64_t e);
__attribute__((interrupt)) void exc_page_fault(struct exc_stack_frame *sf,
                                               uint64_t e);
__attribute__((interrupt)) void exc_x87_fp(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_align_chk(struct exc_stack_frame *sf,
                                              uint64_t e);
__attribute__((interrupt)) void exc_machine_chk(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_simd_fp(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_virt(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_cp(struct exc_stack_frame *sf, uint64_t e);
__attribute__((interrupt)) void exc_hv_inject(struct exc_stack_frame *sf);
__attribute__((interrupt)) void exc_vmmc(struct exc_stack_frame *sf,
                                         uint64_t e);
__attribute__((interrupt)) void exc_security(struct exc_stack_frame *sf,
                                             uint64_t e);

#endif

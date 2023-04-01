#ifndef SYS_IDT_H__
#define SYS_IDT_H__

#include <stdint.h>

struct idtr {
	uint16_t size;
	uint64_t base;
} __attribute__((packed));

struct idt_entry {
	uint16_t base_0;
	uint16_t sel;
	uint8_t ist;
	uint8_t type_attr;
	uint16_t base_1;
	uint32_t base_2;
	uint32_t _zero;
} __attribute__((packed));

enum idt_gate_type {
	IDT_GATE_TYPE_INTERRUPT = 0x8e,
	IDT_GATE_TYPE_TRAP = 0x8f,
};

void idt_load(struct idtr const *idtr);
void idt_init(void);

#endif

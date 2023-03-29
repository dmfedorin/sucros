DISK_BUILD_DIR := sucros-root

OUT_DISK_IMG := sucros.img
KERNEL_BIN := kernel/$(K_OUT_BIN)
LIMINE_BOOT_FILES := \
	deps/limine/limine.sys \
	deps/limine/limine-cd-efi.bin \
	deps/limine/limine-cd.bin

XR := xorriso
EMU := qemu-system-x86_64

XRFLAGS := \
	-as mkisofs \
	-b limine-cd.bin \
	-no-emul-boot \
	-boot-load-size 4 \
	-boot-info-table \
	--efi-boot limine-cd-efi.bin \
	-efi-boot-part \
	--efi-boot-image \
	--protective-msdos-label

EMUFLAGS := -cpu qemu64 -m 4G

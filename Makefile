include kernel/config.mk
include config.mk

all: $(OUT_DISK_IMG)

run: $(OUT_DISK_IMG)
	$(EMU) $(EMUFLAGS) -cdrom $<

$(OUT_DISK_IMG): $(KERNEL_BIN)
	mkdir -p $(DISK_BUILD_DIR)/boot
	cp $(LIMINE_BOOT_FILES) $(DISK_BUILD_DIR)
	cp $< $(DISK_BUILD_DIR)/boot
	$(XR) $(XRFLAGS) -o $@ $(DISK_BUILD_DIR)
	./deps/limine/limine-deploy $@

clean:
	rm -f $(OUT_DISK_IMG)
	make -C kernel clean

$(KERNEL_BIN):
	make -C kernel

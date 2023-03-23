include config.mk

C_SOURCES := $(shell find $(K_SRC_DIR) -name *.c)
S_SOURCES := $(shell find $(K_SRC_DIR) -name *.s)
ALL_SOURCES := $(C_SOURCES) $(S_SOURCES)
OBJECTS := $(patsubst $(K_SRC_DIR)/%, $(K_LIB_DIR)/%.o, $(ALL_SOURCES))

all: $(K_OUT_BIN)

clean:
	rm -rf $(K_LIB_DIR)
	rm -f $(K_OUT_BIN)

$(K_OUT_BIN): $(OBJECTS)
	$(K_LD) $(K_LDFLAGS) -o $@ $^
	chmod -x $@

$(K_LIB_DIR)/%.s.o: $(K_SRC_DIR)/%.s
	@ mkdir -p $@
	@ rmdir $@
	$(K_AS) $(K_ASFLAGS) -o $@ $<

$(K_LIB_DIR)/%.c.o: $(K_SRC_DIR)/%.c
	@ mkdir -p $@
	@ rmdir $@
	$(K_CC) $(K_CFLAGS) -o $@ $<

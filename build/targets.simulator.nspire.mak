ZEHNFLAGS = --name "epsilon"

$(BUILD_DIR)/%.tns: $(BUILD_DIR)/%.elf
	$(GENZEHN) --input $^ --output $@ $(ZEHNFLAGS)

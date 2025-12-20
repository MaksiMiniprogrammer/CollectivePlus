include Commons.mk

all: clean init build_core

build_core:
	$(MAKE) -C $(PROJ_PATH_CORE)/

init:
	mkdir -p $(RESULT_PATH)
	mkdir -p $(RESULT_BIN)
	mkdir -p $(RESULT_INCLUDE)
	mkdir -p $(RESULT_LIB)
	mkdir -p $(RESULT_OBJ)

clean:
	rm -rf $(RESULT_PATH)

.PHONY: all init clean
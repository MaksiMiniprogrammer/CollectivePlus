include ../Commons.mk

TARGET = collective_plus_core

SRC = $(wildcard $(MAIN_PATH)/$(PROJ_PATH_CORE)/*.c)
OBJ = $(patsubst $(MAIN_PATH)/$(PROJ_PATH_CORE)/%.c, $(RESULT_OBJ)/$(PROJ_PATH_CORE)/%.o, $(SRC))
HEADERS = $(wildcard $(MAIN_PATH)/$(PROJ_PATH_CORE)/*.h)

all: init install $(RESULT_BIN)/$(TARGET)

init:
	mkdir -p $(RESULT_INCLUDE)/$(PROJ_PATH_CORE)
	mkdir -p $(RESULT_OBJ)/$(PROJ_PATH_CORE)
	mkdir -p $(RESULT_BIN)

install:
	cp $(HEADERS) $(RESULT_INCLUDE)/$(PROJ_PATH_CORE)

$(RESULT_BIN)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(RESULT_OBJ)/$(PROJ_PATH_CORE)/%.o: $(MAIN_PATH)/$(PROJ_PATH_CORE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(RESULT_INCLUDE)/$(PROJ_PATH_CORE)
	rm -rf $(RESULT_OBJ)/$(PROJ_PATH_CORE)
	rm -f $(RESULT_BIN)/$(TARGET)

.PHONY: all init clean install

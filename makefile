BUILD_DIR ?= build
SOURCE_DIR ?= src
INCLUDE_DIR ?= include
LIB_DIR ?= lib

SOURCES := $(shell find $(SOURCE_DIR) -name '*.c') $(shell find $(SOURCE_DIR) -name '*.cpp')
OBJECTS_1 := $(SOURCES:%.c=%.o)
OBJECTS := $(OBJECTS_1:%.cpp=%.o)
OUTPUTS := $(OBJECTS:src%=build%)

C_FLAGS ?= -Wall -Wpedantic -Wno-gnu -Wno-newline-eof -Wno-unused-function -Wno-unneeded-internal-declaration

all: $(LIB_DIR)/libmmanager.a test.o

test.o: test.c | $(LIB_DIR)/libmmanager.a
	$(CC) $(C_FLAGS) -O3 -I$(INCLUDE_DIR) $^ -o $@ -L$(LIB_DIR) -lmmanager

$(LIB_DIR)/libmmanager.a: $(OUTPUTS)
	ar cr $@ $^

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(C_FLAGS) -O3 -I$(INCLUDE_DIR) -o $@ $< -c

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(C_FLAGS) -O3 -I$(INCLUDE_DIR) -o $@ $< -c

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(LIB_DIR)
	rm -rf test.o
NAME := examples
CC := gcc
CC_FLAGS := -g -Wall -Wpedantic -Wextra -Wconversion -O2 # compiler flags
CPP_FLAGS := -MMD -MP -I../src/inc # preprocessor flags
LD_FLAGS := -L../build -larithmathic -lm

BUILD_DIR := ../build/$(NAME)
OBJ_DIR := $(BUILD_DIR)/obj
SRC_DIR := .

SOURCES := $(wildcard $(SRC_DIR)/*.c)
DEPS := $(patsubst $(SRC_DIR)/%.c, %.d, $(SOURCES))

.PHONY: all directories clean
all: directories arith_lib $(NAME)

directories:
	mkdir -p $(BUILD_DIR)

arith_lib:
	$(MAKE) -C ../src # run library makefile

clean:
	rm -rf $(BUILD_DIR)

$(NAME): $(SOURCES:.c=) # remove .c from target

.c:
	$(CC) $(CPP_FLAGS) $(CC_FLAGS) $< -o $(BUILD_DIR)/$@ $(LD_FLAGS)

-include $(DEPS)
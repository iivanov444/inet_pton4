# Compiler and flags
CC             = gcc
# CC	       = clang
CFLAGS         = -I./include -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -Wno-comment #-std=c89
LDFLAGS        = -Llib

# Directories
SRC_DIR        = src
INC_DIR        = include
LIB_DIR        = lib
BUILD_DIR      = build
OBJ_DIR        = $(BUILD_DIR)/obj
BIN_DIR        = $(BUILD_DIR)/bin
DEPS_DIR       = $(BUILD_DIR)/.deps

# Files
MAIN           = main.c
SRCS           = $(filter-out $(SRC_DIR)/$(MAIN), $(wildcard $(SRC_DIR)/*.c))
SRCS_WITH_MAIN = $(wildcard $(SRC_DIR)/*.c)

OBJS           = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
MAIN_OBJ       = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_DIR)/$(MAIN))
ALL_OBJS       = $(OBJS) $(MAIN_OBJ)

TARGET         = $(BIN_DIR)/main


# Default target with sanitizers
all: CFLAGS += -fsanitize=address -fsanitize=leak
all: LDFLAGS += -fsanitize=address -fsanitize=leak
all: $(TARGET)


# Create directories
$(OBJ_DIR) $(BIN_DIR):
	@mkdir -p $@

# Link object files to create executable
$(TARGET): $(ALL_OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# Debug build with sanitizers
debug: CFLAGS += -DDEBUG -g3 -O0 -fsanitize=address -fsanitize=leak
debug: LDFLAGS += -fsanitize=address -fsanitize=leak
debug: clean all


# Release builds:

# Dynamic link with O2 optimization and with sanitizers
release_dynamic_O2: CFLAGS += -DNDEBUG -march=native -O2 -g0 -fsanitize=address -fsanitize=leak
release_dynamic_O2: LDFLAGS += -fsanitize=address -fsanitize=leak
release_dynamic_O2: clean all

# Dynamic link with Os optimization and with sanitizers
release_dynamic_Os: CFLAGS += -DNDEBUG -march=native -Os -g0 -fsanitize=address -fsanitize=leak
release_dynamic_Os: LDFLAGS += -fsanitize=address -fsanitize=leak
release_dynamic_Os: clean all

# Static link with O2 optimization and no sanitizers
release_static_O2: CFLAGS = -Iinclude -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -DNDEBUG -march=native -O2 -g0
release_static_O2: LDFLAGS = -Llib -static
release_static_O2: clean $(TARGET)

# Static link with Os optimization and no sanitizers
release_static_Os: CFLAGS = -Iinclude -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -DNDEBUG -march=native -Os -g0
release_static_Os: LDFLAGS = -Llib -static
release_static_Os: clean $(TARGET)


# Run the program
run: $(TARGET)
	./$(TARGET)


# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)


# Install - uncomment the desired release for install
# Left commented out on purpose

# install: release_dynamic_O2
#	cp $(TARGET) /usr/local/bin/

# install: release_dynamic_Os
#	cp $(TARGET) /usr/local/bin/

# install: release_static_O2
#	cp $(TARGET) /usr/local/bin/

# install: release_static_Os
#	cp $(TARGET) /usr/local/bin/


# Test
test: debug
	./$(TARGET)


# Create DEPS_DIR
$(DEPS_DIR):
	@mkdir -p $@

# Dependency files pattern
DEPFILES = $(patsubst $(SRC_DIR)/%.c, $(DEPS_DIR)/%.d, $(SRCS_WITH_MAIN))

# Include dependency files
-include $(DEPFILES)

# Generate dependency files
$(DEPS_DIR)/%.d: $(SRC_DIR)/%.c | $(DEPS_DIR)
	@$(CC) $(CFLAGS) -MM -MT $(OBJ_DIR)/$*.o -MF $@ $<

.PHONY: all clean run debug release_dynamic_O2 release_dynamic_Os release_static_O2 release_static_Os install test

# === Compiler and flags ===
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program

# === Directories ===
SRC_DIR = src
MEM_DIR = $(SRC_DIR)/memory
PROG_DIR = $(SRC_DIR)/Program
TEST_DIR = test
BIN_DIR = bin
LIB_DIR = lib

# === Memory allocation sources ===
MEMORY_SRCS = \
	$(PROG_DIR)/memory_allocation.c \
	$(MEM_DIR)/dmalloc.c \
	$(MEM_DIR)/dcalloc.c \
	$(MEM_DIR)/drealloc.c \
	$(MEM_DIR)/dfree.c

MEMORY_OBJS = $(MEMORY_SRCS:.c=.o)

# === Data structure sources ===
DS_SRCS = \
	$(PROG_DIR)/Linked_list.c \
	$(PROG_DIR)/Stack.c \
	$(PROG_DIR)/queue.c \
	$(PROG_DIR)/HashMap.c \
	$(PROG_DIR)/BST.c

DS_OBJS = $(DS_SRCS:.c=.o)

# === Test source ===
TEST_DS_SRC = $(TEST_DIR)/test_data_structures.c
TEST_DS_OBJ = $(TEST_DS_SRC:.c=.o)
TEST_DS_BIN = $(BIN_DIR)/test_data_structures.exe

# CLI App
CLI_SRC = $(PROG_DIR)/currc_main.c
CLI_EXE = $(BIN_DIR)/currc.exe

# === Default target ===
all: $(LIB_DIR)/libcurrc.a $(LIB_DIR)/libcurrc.so $(LIB_DIR)/currc.dll $(TEST_DS_BIN) $(CLI_EXE)

# === Compile Rules ===
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# === Executable Linking ===
$(TEST_DS_BIN): $(TEST_DS_OBJ) $(DS_OBJS) $(MEMORY_OBJS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(CLI_EXE): $(CLI_SRC) $(DS_OBJS) $(MEMORY_OBJS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# === Build Static Library ===
$(LIB_DIR)/libcurrc.a: $(DS_OBJS) $(MEMORY_OBJS)
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)
	ar rcs $@ $^

# === Build Shared Library for Linux/macOS (.so) ===
$(LIB_DIR)/libcurrc.so: $(DS_OBJS) $(MEMORY_OBJS)
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)
	$(CC) -shared -o $@ $^

# === Build DLL for Windows ===
$(LIB_DIR)/currc.dll: $(DS_OBJS) $(MEMORY_OBJS)
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)
	$(CC) -shared -o $@ $^

# === Clean ===
clean:
	-del /q $(MEMORY_OBJS) $(DS_OBJS) $(TEST_DS_OBJ) $(CLI_EXE) $(TEST_DS_BIN) 2>nul
	-del /q $(LIB_DIR)\libcurrc.a $(LIB_DIR)\libcurrc.so $(LIB_DIR)\currc.dll 2>nul

# === Full Rebuild ===
rebuild: clean all

.PHONY: all clean rebuild

# === Compiler and flags ===
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -Isrc

# === Directories ===
SRC_DIR = src
MEM_DIR = $(SRC_DIR)/memory
TEST_DIR = test
BIN_DIR = bin
LIB_DIR = lib

# === Memory allocation sources ===
MEMORY_SRCS = \
	$(SRC_DIR)/memory_allocation.c \
	$(MEM_DIR)/dmalloc.c \
	$(MEM_DIR)/dcalloc.c \
	$(MEM_DIR)/drealloc.c \
	$(MEM_DIR)/dfree.c

MEMORY_OBJS = $(MEMORY_SRCS:.c=.o)

# === Data structure sources ===
DS_SRCS = \
	$(SRC_DIR)/Linked_list.c \
	$(SRC_DIR)/Stack.c \
	$(SRC_DIR)/queue.c \
	$(SRC_DIR)/HashMap.c \
	$(SRC_DIR)/BST.c

DS_OBJS = $(DS_SRCS:.c=.o)

# === Test source ===
TEST_SRC = $(TEST_DIR)/test_ds.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_BIN = $(BIN_DIR)/test_ds.exe

TEST_DS_SRC = $(TEST_DIR)/test_data_structures.c
TEST_DS_OBJ = $(TEST_DS_SRC:.c=.o)
TEST_DS_BIN = $(BIN_DIR)/test_data_structures.exe

# === Default target ===
all: $(TEST_BIN) $(TEST_DS_BIN) $(LIB_DIR)/libcurrc.a

# === Compile Rules ===
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# === Final linking ===
$(TEST_BIN): $(TEST_OBJ) $(DS_OBJS) $(MEMORY_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_DS_BIN): $(TEST_DS_OBJ) $(DS_OBJS) $(MEMORY_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# === Build Static LIbrary ==
$(LIB_DIR)/libcurrc.a: $(DS_OBJS) $(MEMORY_OBJS)
	mkdir -p $(LIB_DIR)
	ar rcs $@ $^


# === Clean ===
clean:
	rm -f $(DS_OBJS) $(MEMORY_OBJS) $(TEST_OBJ) $(TEST_BIN) $(TEST_DS_OBJ) $(TEST_DS_BIN)

# === Full Rebuild ===
rebuild: clean all

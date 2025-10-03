ifeq ($(findstring cl,$(CC)),cl)
    CFLAGS = /nologo /EHsc /MD /Iinclude /Isrc /Isrc/Program
    OUTFLAG = /Fe
    OBJFLAG = /Fo
    SHARED = /LD
    AR = lib
    ARFLAGS = /OUT:
else
    CFLAGS = -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program
    OUTFLAG = -o
    OBJFLAG =
    SHARED = -shared
    AR = ar
    ARFLAGS = rcs
endif

# Fix AR and ARFLAGS for Windows with gcc
ifeq ($(OS),Windows_NT)
    ifneq ($(findstring cl,$(CC)),cl)
        AR = ar
        ARFLAGS = rcs
    else
        AR = lib
        ARFLAGS =
    endif
endif

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
TEST_DS_BIN = $(BIN_DIR)/test_data_structures$(EXE)

# CLI App
CLI_SRC = $(PROG_DIR)/currc_main.c
CLI_EXE = $(BIN_DIR)/currc$(EXE)

# === Default target ===
all: $(LIB_DIR)/libcurrc.a $(LIB_DIR)/libcurrc.so $(LIB_DIR)/currc.dll $(TEST_DS_BIN) $(CLI_EXE)

# === Compile Rules ===
ifeq ($(OS),Windows_NT)
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@
else
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@
endif

ifeq ($(OS),Windows_NT)
$(TEST_DS_BIN): $(TEST_DS_OBJ) $(DS_OBJS) $(MEMORY_OBJS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) $(OUTFLAG) $@ $^

$(CLI_EXE): $(CLI_SRC) $(DS_OBJS) $(MEMORY_OBJS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) $(OUTFLAG) $@ $^
else
$(TEST_DS_BIN): $(TEST_DS_SRC) $(DS_OBJS) $(MEMORY_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(CLI_EXE): $(CLI_SRC) $(DS_OBJS) $(MEMORY_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@
endif

# === Build Static Library ===
ifeq ($(OS),Windows_NT)
$(LIB_DIR)/libcurrc.a: $(DS_OBJS) $(MEMORY_OBJS)
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^
else
$(LIB_DIR)/libcurrc.a: $(DS_OBJS) $(MEMORY_OBJS)
	@mkdir -p $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^
endif

# === Build Shared Library for Linux/macOS (.so) ===
$(LIB_DIR)/libcurrc.so: $(DS_OBJS) $(MEMORY_OBJS)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $^

# === Build DLL for Windows ===
ifeq ($(OS),Windows_NT)
$(LIB_DIR)/currc.dll: $(DS_OBJS) $(MEMORY_OBJS)
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)
	$(CC) $(CFLAGS) $(SHARED) $(OUTFLAG)$@ $^
else
$(LIB_DIR)/currc.dll: $(DS_OBJS) $(MEMORY_OBJS)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $^
endif

# === Clean ===
ifeq ($(OS),Windows_NT)
clean:
    -$(RM) $(MEMORY_OBJS) $(DS_OBJS) $(TEST_DS_OBJ) $(CLI_EXE) $(TEST_DS_BIN) 2>nul
    -$(RM) $(LIB_DIR)\libcurrc.a $(LIB_DIR)\libcurrc.so $(LIB_DIR)\currc.dll 2>nul
else
clean:
    $(RM) $(MEMORY_OBJS) $(DS_OBJS) $(TEST_DS_OBJ) $(CLI_EXE) $(TEST_DS_BIN)
    $(RM) $(LIB_DIR)/libcurrc.a $(LIB_DIR)/libcurrc.so $(LIB_DIR)/currc.dll
endif

# === Full Rebuild ===
rebuild: clean all

.PHONY: all clean rebuild
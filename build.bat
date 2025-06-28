@echo off
REM Build script for Curr.c project using gcc (MinGW)

REM Create bin directory if it doesn't exist
if not exist bin (
    mkdir bin
)

REM Compile memory allocation sources
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/Program/memory_allocation.c -o ./src/Program/memory_allocation.o
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/memory/dmalloc.c -o ./src/memory/dmalloc.o
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/memory/dcalloc.c -o ./src/memory/dcalloc.o
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/memory/drealloc.c -o ./src/memory/drealloc.o
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/memory/dfree.c -o ./src/memory/dfree.o

REM Compile data structure sources
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/Program/Linked_list.c -o ./src/Program/Linked_list.o
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/Program/Stack.c -o ./src/Program/Stack.o
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/Program/queue.c -o ./src/Program/queue.o
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/Program/HashMap.c -o ./src/Program/HashMap.o
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./src/Program/BST.c -o ./src/Program/BST.o

REM Compile test source
gcc -Wall -Wextra -g -Iinclude -Isrc -Isrc/Program -c ./test/test_data_structures.c -o ./test/test_data_structures.o

REM Link all object files into executable
gcc -g ./src/Program/memory_allocation.o ./src/memory/dmalloc.o ./src/memory/dcalloc.o ./src/memory/drealloc.o ./src/memory/dfree.o ./src/Program/Linked_list.o ./src/Program/Stack.o ./src/Program/queue.o ./src/Program/HashMap.o ./src/Program/BST.o ./test/test_data_structures.o -o ./bin/test_data_structures.exe

echo Build completed.

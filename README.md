# malloc_manager
 
Simple drop in replacement for `malloc` and `free` that keeps track of allocations and warns about unfreed pointers.

Build with `make`, link with `lib/libmmanager.a` and include `include/malloc_manager.h`.

If you don't want to have `malloc` and `free` redefined, `#define DONT_REDEFINE_MALLOC` before including `malloc_manager.h`.

Wrap a block for printing debug information with `DEBUG_MALLOC_MANAGER_ON;` and `DEBUG_MALLOC_MANAGER_OFF;`.

See `test.c` for an example.
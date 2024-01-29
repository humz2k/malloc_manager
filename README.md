# malloc_manager
 
Simple drop in replacement for `malloc` and `free` that keeps track of allocations and warns about unfreed pointers.

Build with `make`, link with `lib/libmmanager.a` and include `include/malloc_manager.h`. You will need to force `ld` to link ALL libraries. Either use `-Wl,--whole-archive` or call `force_linking_malloc_manager()` in `main()`.

If you don't want to have `malloc` and `free` redefined, `#define DONT_REDEFINE_MALLOC` before including `malloc_manager.h`, and use `SMART_MALLOC` and `SMART_FREE`.

Wrap a block for printing debug information with `DEBUG_MALLOC_MANAGER_ON;` and `DEBUG_MALLOC_MANAGER_OFF;`.

See `test.c` for an example.
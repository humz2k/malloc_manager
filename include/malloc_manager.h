#ifndef _MALLOC_MANAGER_H_
#define _MALLOC_MANAGER_H_

#include <stdlib.h>

struct malloc_manager;

#ifdef __cplusplus
extern "C" {
#endif

void* smart_malloc(size_t sz, int line, const char* file);
void smart_free(void* ptr);
void* smart_realloc(void* ptr, size_t sz, int line, const char* file);

void turn_on_debug_malloc_manager();
void turn_off_debug_malloc_manager();

void print_alive_allocations();

#ifdef __cplusplus
}
#endif

#define DEBUG_MALLOC_MANAGER_ON turn_on_debug_malloc_manager()
#define DEBUG_MALLOC_MANAGER_OFF turn_off_debug_malloc_manager()

#define SMART_MALLOC(sz) smart_malloc(sz,__LINE__,__FILE__)
#define SMART_FREE(ptr) smart_free(ptr)
#define SMART_REALLOC(ptr,sz) smart_realloc(ptr,sz,__LINE__,__FILE__)

#define DEBUG_MEM 

#ifndef DONT_REDEFINE_MALLOC

#define malloc(sz) SMART_MALLOC(sz)
#define free(ptr) SMART_FREE(ptr)
#define realloc(ptr,sz) SMART_REALLOC(ptr,sz)

#endif

#endif
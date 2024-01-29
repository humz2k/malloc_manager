#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define DONT_REDEFINE_MALLOC
#include "malloc_manager.h"

#define DEBUG

static int debug_malloc_manager_on = 0;

#ifdef DEBUG
#define log(...) if(debug_malloc_manager_on){printf("LOG<malloc_manager.c>: "); printf(__VA_ARGS__); printf("\n");}
#else
#define log(...)
#endif

void turn_on_debug_malloc_manager(){
    debug_malloc_manager_on = 1;
    log("debug mode on");
}

void turn_off_debug_malloc_manager(){
    if (debug_malloc_manager_on){
        print_alive_allocations();
        log("debug mode off");
    }
    debug_malloc_manager_on = 0;
}

struct allocation{
    void* ptr;
    int line;
    const char* file;
};

struct malloc_manager{
    int n_alive;
    int n_total;
    struct allocation* alive_allocations;
};

static struct malloc_manager mmanager;

void init_malloc_manager(){
    mmanager.n_total = 0;
    mmanager.n_alive = 0;
    mmanager.alive_allocations = NULL;
    log("init_malloc_manager called");
}

static void add_allocation(void* allocation, int line, const char* file){
    log("allocated %p (%s:%d)",allocation,file,line);
    mmanager.n_alive++;
    if (mmanager.alive_allocations == NULL){
        assert(mmanager.n_alive == 1);
        mmanager.alive_allocations = (struct allocation*)malloc(sizeof(struct allocation) * mmanager.n_alive);
    } else {
        assert(mmanager.n_alive > 1);
        mmanager.alive_allocations = (struct allocation*)realloc(mmanager.alive_allocations,sizeof(struct allocation) * mmanager.n_alive);
    }
    mmanager.alive_allocations[mmanager.n_alive - 1].ptr = allocation;
    mmanager.alive_allocations[mmanager.n_alive - 1].line = line;
    mmanager.alive_allocations[mmanager.n_alive - 1].file = file;
}

void* smart_malloc(size_t sz, int line, const char* file){
    void* out = malloc(sz);
    add_allocation(out,line, file);
    return out;
}

void smart_free(void* ptr){
    log("freeing %p",ptr);
    int idx = -1;
    for (int i = 0; i < mmanager.n_alive; i++){
        if (mmanager.alive_allocations[i].ptr == ptr){
            idx = i;
            break;
        }
    }
    if (idx == -1){
        printf("WARNING: trying to free pointer not in mmanager(?)\n");
        free(ptr);
        return;
    }
    free(mmanager.alive_allocations[idx].ptr);
    mmanager.n_alive--;
    assert(mmanager.n_alive >= 0);
    if (mmanager.n_alive == 0){
        free(mmanager.alive_allocations);
        mmanager.alive_allocations = NULL;
        return;
    }
    struct allocation* new_allocations = (struct allocation*)malloc(sizeof(struct allocation) * mmanager.n_alive);
    for (int i = 0; i < idx; i++){
        new_allocations[i] = mmanager.alive_allocations[i];
    }
    for (int i = idx; i < mmanager.n_alive; i++){
        new_allocations[i] = mmanager.alive_allocations[i+1];
    }
    free(mmanager.alive_allocations);
    mmanager.alive_allocations = new_allocations;
}

void finalize_malloc_manager(){
    log("finalize_malloc_manager called");
    assert(mmanager.n_alive >= 0);
    if (mmanager.n_alive > 0){
        assert(mmanager.alive_allocations != NULL);
        printf("WARNING: %d unfreed %s!\n",mmanager.n_alive,mmanager.n_alive == 1 ? "pointer" : "pointers");
        for (int i = 0; i < mmanager.n_alive; i++){
            assert(mmanager.alive_allocations[i].ptr != NULL);
            printf(" - %s:%d -> %p\n",mmanager.alive_allocations[i].file,mmanager.alive_allocations[i].line,mmanager.alive_allocations[i].ptr);
            free(mmanager.alive_allocations[i].ptr);
        }
    } else {
        log("no unfreed pointers");
    }
}

void print_alive_allocations(){
    if (mmanager.n_alive == 0){
        printf("LOG<malloc_manager.c>: no pointers alive\n");
        return;
    }
    printf("LOG<malloc_manager.c>: alive pointers:\n");
    for (int i = 0; i < mmanager.n_alive; i++){
        assert(mmanager.alive_allocations[i].ptr != NULL);
        printf(" - %s:%d -> %p\n",mmanager.alive_allocations[i].file,mmanager.alive_allocations[i].line,mmanager.alive_allocations[i].ptr);
    }
}
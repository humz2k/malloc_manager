#include "malloc_manager.h"

int* my_func(){
    
    int* ptr1 = malloc(sizeof(int) * 1000);
    return ptr1;
}

int main(){
    DEBUG_MALLOC_MANAGER_ON;
    int* ptr = malloc(sizeof(int) * 3);
    int* out = my_func();

    ptr = realloc(ptr,sizeof(int) * 10);

    free(out);
    free(ptr);
    DEBUG_MALLOC_MANAGER_OFF;
    return 0;
}
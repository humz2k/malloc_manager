#include "malloc_manager.h"

int* my_func(){
    DEBUG_MALLOC_MANAGER_ON;
    int* ptr1 = malloc(sizeof(int) * 1000);
    DEBUG_MALLOC_MANAGER_OFF;
    return ptr1;
}

int main(){
    int* ptr = malloc(sizeof(int) * 3);
    int* out = my_func();
    free(out);
    free(ptr);
    return 0;
}
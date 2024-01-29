#include "malloc_manager.h"

int main(){
    
    DEBUG_MALLOC_MANAGER_ON;
    int array_sz = 100;
    int* my_array = (int*)malloc(sizeof(int) * array_sz);
    free(my_array);
    DEBUG_MALLOC_MANAGER_OFF;
    return 0;
}
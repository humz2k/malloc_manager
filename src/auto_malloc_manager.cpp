#include "malloc_manager.h"
#include <stdio.h>

extern "C" void init_malloc_manager();
extern "C" void finalize_malloc_manager();

class AutoMallocManager{
    public:
        AutoMallocManager(){
            init_malloc_manager();
        }

        ~AutoMallocManager(){
            finalize_malloc_manager();
        }
};

extern "C" int link_me_malloc_manager(){
    return 5;
}

AutoMallocManager a;
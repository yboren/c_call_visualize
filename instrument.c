#include<stdio.h>
#include<stdlib.h>

void __cyg_profile_func_enter(void *func_address, void *callsite)
    __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *func_address, void *callsite)
    __attribute__((no_instrument_function));

void main_constructor(void)
    __attribute__((no_instrument_function, constructor));

void main_destructor(void)
    __attribute__((no_instrument_function, destructor));

static FILE *fp;

void __cyg_profile_func_enter(void *this, void *callsite)
{
    fprintf(fp, "E%p\n", (int *)this);
}

void __cyg_profile_func_exit(void *this, void *callsite)
{
    fprintf(fp, "X%p\n", (int *)this);
}

void main_constructor(void)
{
    fp = fopen("trace.txt", "w");
    if (fp == NULL){
        exit(-1);
    }
}



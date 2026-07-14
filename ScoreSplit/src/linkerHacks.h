#pragma once
//stolen from Khangaroo

#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <concrt.h>
// Sorry

void* __cdecl operator new(unsigned int size) {
    return malloc(size); // Exceptions are overrated anyway
}

void __cdecl operator delete(void* addr) noexcept {
    free(addr);
}

void __cdecl operator delete(void* addr, unsigned int size) {
    free(addr);
}

int __cdecl atexit(void(*)()) {
    return 0;
}

namespace stdext {
    class exception;
}

namespace std {
    void(__cdecl* _Raise_handler)(class stdext::exception const&) = nullptr;
}
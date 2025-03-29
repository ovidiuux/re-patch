#include "ARM.h"

void patch_function(void* target, void* replacement) {
    void* page = (void*)((uintptr_t)target & ~(getpagesize() - 1));

    if (mprotect(page, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
        return;
    }

    uint32_t* instr = (uint32_t*)target;
    instr[0] = 0x58000051; // LDR X17, #16
    instr[1] = 0xD61F0220; // BR X17
    *(void**)((char*)target + 8) = replacement;

    __builtin___clear_cache((char*)target, (char*)target + 12);
}
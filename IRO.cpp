/*
* 
* Grand Theft Auto: Vice City 1.12 Android 
* Patch arm64-v8a
* irostudio.eu.org
*
*/

#include <dlfcn.h>
#include <sys/mman.h>

#define LOG_TAG "IRO"
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

typedef void (*DebugLog_t)(char* param_1, ...);
DebugLog_t orig_DebugLog = nullptr;

void hooked_DebugLog(char* param_1) {
    ALOGI("DebugLog called: %s", param_1);
    return;
}

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

__attribute__((constructor)) void init() {
    ALOGI("patch");

    void* lib_handle = dlopen("libGTAVC.so", RTLD_NOW);
    if (!lib_handle) {
        return;
    }

    orig_DebugLog = (DebugLog_t)dlsym(lib_handle, "_ZN6CDebug8DebugLogEPKcz");
    if (!orig_DebugLog) {
        dlclose(lib_handle);
        return;
    }

    patch_function((void*)orig_DebugLog, (void*)hooked_DebugLog);
}
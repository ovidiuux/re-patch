/*
* 
* Grand Theft Auto: Vice City 1.12 Android 
* Patch arm64-v8a
* irostudio.eu.org
*
*/

#include "ARM.h"

#define LOG_TAG "IRO"
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

typedef void (*DebugLog_t)(char* param_1, ...);
DebugLog_t orig_DebugLog = nullptr;

void hooked_DebugLog(char* param_1) {
    ALOGI("DebugLog called: %s", param_1);
    return;
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
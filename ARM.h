#pragma once
#include <dlfcn.h>
#include <sys/mman.h>

void patch_function(void* target, void* replacement);
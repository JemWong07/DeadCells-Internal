#pragma once
#include <vector>
#include <Windows.h>

void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);

void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);

void Patch(BYTE* dst, BYTE* src, unsigned int size);

void Nop(BYTE* dst, unsigned int size);

uintptr_t FindDynamicAddr(uintptr_t basePtr, std::vector<unsigned int> offsets);
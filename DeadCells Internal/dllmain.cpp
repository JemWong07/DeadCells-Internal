// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "Mem.h"
#include "Proc.h"

BOOL WINAPI HackThread(HMODULE hModule)
{
    //  Create Console.
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "OK OK OK\n";

    //  Get Mobule Base.
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"libhl.dll");

    bool bPotion = false, bJump = false, bInstantHeal = false, bAmmo = false, bCD = false;

    //  Hack Loop.
    while (true)
    {
        //  Get Keyinput.
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bInstantHeal = !bInstantHeal;
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bPotion = !bPotion;
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bJump = !bJump;
        }
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            bAmmo = !bAmmo;
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            bCD = !bCD;
            std::cout << bCD << '\n';
        }
        if (GetAsyncKeyState(VK_NUMPAD6) & 1)
        {
            *(int*)FindDynamicAddr(moduleBase + 0x48184, { 0xA50, 0x8, 0x38, 0x5C, 0x2C }) += 10000;
        }
        if (GetAsyncKeyState(VK_NUMPAD7) & 1)
        {
            *(int*)FindDynamicAddr(moduleBase + 0x48184, { 0x634, 0x0, 0x18, 0x64, 0x338 }) += 10000;
        }
        if (GetAsyncKeyState(VK_NUMPAD9) & 1)
        {
            std::cout << "1\n";
        }

        //  Freeze.
        if (bInstantHeal)
        {
            *(int*)FindDynamicAddr(moduleBase + 0x48184, { 0x424, 0x8, 0x58, 0x64, 0xFC }) = 100;
        }
        if (bPotion)
        {
            *(int*)FindDynamicAddr(moduleBase + 0x48184, { 0x634, 0x0, 0x18, 0x64, 0x300 }) = 10;
        }
        if (bJump)
        {
            *(int*)FindDynamicAddr(moduleBase + 0x48184, { 0x42C, 0x0, 0x58, 0x64, 0x290 }) = 0;
        }
        if (bAmmo)
        {
            *(int*)FindDynamicAddr(moduleBase + 0x48184, { 0x62C, 0x0, 0x18, 0x88, 0xF8, 0x1C }) = 10;
            *(int*)FindDynamicAddr(moduleBase + 0x48184, { 0x62C, 0x0, 0x18, 0x8C, 0xF8, 0x1C }) = 10;
        }
        if (bCD)
        {
            *(int*)FindDynamicAddr(moduleBase + 0x48184, { 0x634, 0x0, 0x18, 0x64, 0x2E8, 0x3F4 }) = 0;
            *(int*)FindDynamicAddr(moduleBase + 0x48184, { 0x634, 0x0, 0x18, 0x64, 0x2E8, 0x50C }) = 0;
        }
        Sleep(5);
    }

    //  Clean & Reject.
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


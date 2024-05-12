/*
Written by: @nu11charb
Course: Offensive Development and Tradecraft (https://ask-academy.live/courses/offensive-development-and-tradecraft)
Purpose: This code is used to check if a debugger is present via isDebuggerPresent Api.
*/

#include <stdio.h>
#include <windows.h>

void IsDebuggerPresentCheckViaApi();
void IsRemoteDebuggerPresent();
void CheckDebuggerViaNTGlobalFlag();
void CheckDebuggerViaNTQueryInformationProcess();

int main(void) {
    printf("[i] [Func: %s] Checking for Debugger Present.\n", __func__);

    IsDebuggerPresentCheckViaApi();
    IsRemoteDebuggerPresent();
    CheckDebuggerViaNTGlobalFlag();
    CheckDebuggerViaNTQueryInformationProcess();

    printf("[i] [Func: %s] Press any key to continue.", __func__);

    getchar();

    return 0;
}

void IsDebuggerPresentCheckViaApi() {
    BOOL isDebuggerPresent = IsDebuggerPresent();

    if (isDebuggerPresent){
        printf("[-] [Func: %s] Debugger is Found.\n", __func__);
    }
    else{
        printf("[+] [Func: %s] No Debugger Found.\n", __func__);
    }
}

void IsRemoteDebuggerPresent() {
    BOOL isRemoteDebuggerPresent = 0;

    CheckRemoteDebuggerPresent(GetCurrentProcess(), &isRemoteDebuggerPresent);

    if (isRemoteDebuggerPresent){
        printf("[-] [Func: %s] Debugger is Found.\n", __func__);
    }
    else{
        printf("[+] [Func: %s] No Debugger Found.\n", __func__);
    }
}

void CheckDebuggerViaNTGlobalFlag() {
    PDWORD pNtGlobalFlag = NULL;
    VOID* pPeb = (VOID*)__readgsqword(0x60);
    pNtGlobalFlag = (PDWORD)(pPeb + 0xBC);

    if(pNtGlobalFlag && (*pNtGlobalFlag & 0x00000070))
        printf("[-] [Func: %s] Debugger is Found.\n", __func__);
    else
        printf("[+] [Func: %s] No Debugger Found.\n", __func__);
}

// Define PROCESSINFOCLASS enum
typedef enum _PROCESSINFOCLASS {
    ProcessDebugPort = 7
} PROCESSINFOCLASS;

// Define NtQueryInformationProcess function prototype
typedef NTSTATUS (NTAPI *NTQUERYINFORMATIONPROCESS)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);

void CheckDebuggerViaNTQueryInformationProcess() {

    NTQUERYINFORMATIONPROCESS _NtQueryInformationProcess = (NTQUERYINFORMATIONPROCESS) GetProcAddress(
            LoadLibraryA("ntdll.dll"), "NtQueryInformationProcess");

    if (_NtQueryInformationProcess)
    {
        DWORD dwProcessDebugPort;
        DWORD dwProcessInformationLength = sizeof(ULONG) * 2;
        NTSTATUS status = _NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort, &dwProcessDebugPort, dwProcessInformationLength, NULL);

        if (dwProcessDebugPort == -1){
            printf("[-] [Func: %s] Debugger is Found. dwProcessDebugPort = %lu.\n", __func__, dwProcessDebugPort);
        }
        else
            printf("[+] [Func: %s] No Debugger Found.\n", __func__);
    }

}

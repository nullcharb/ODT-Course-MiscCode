/*
Written by: @nu11charb
Course: Offensive Development and Tradecraft (https://ask-academy.live/courses/offensive-development-and-tradecraft)
Purpose: This code is used to check if a debugger is present via isDebuggerPresent Api.
*/

#include <stdio.h>
#include <windows.h>

void IsDebuggerPresentCheckViaApi();
void IsRemoteDebuggerPresent();

int main(void) {
    printf("[i] [Func: %s] Checking for Debugger Present via IsDebuggerPresent Api\n", __func__);

    IsDebuggerPresentCheckViaApi();
    IsRemoteDebuggerPresent();

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


/*
Section details about this pefile.

.text: This section contains the executable code, also known as the program's text segment. The instructions for the program are stored in this section.

.data: This section contains global and static data that is initialized before the program starts running. This includes variables and arrays that are initialized with values.

.rdata: This section contains read-only data that is used by the program. This includes constants and string literals.

.pdata: This section contains information about the exception handling data in the program. It's used by the operating system to handle exceptions that occur during program execution.

.xdata: This section contains exception handling data for the program. It's used to handle exceptions that occur during program execution.

.bss: This section contains uninitialized data. This includes global and static variables that are not initialized with values.

.idata: This section contains information about the program's imported functions and libraries. This information is used by the program to link with other libraries and to call functions from those libraries.

.CRT: This section contains code that is executed before the program starts running. This includes constructors for global and static objects.

.tls: This section contains data for the program's thread-local storage. This includes variables that are unique to each thread.

.reloc: This section contains information about the program's relocation data. It's used to adjust the program's memory addresses when it's loaded into memory.

Each section of a PE file has a specific purpose and contains different types of data. By examining the contents of each section, you can get an idea of what the program does and how it works.
*/
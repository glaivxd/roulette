#include <Windows.h>
#include <time.h>
#include <winternl.h>
#include <stdio.h>

/* stack overflow is so awesome */
void bsod() {
	typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
	typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
    BOOLEAN bEnabled;
    ULONG uResp;
    pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
    pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtRaiseHardError");
    NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
    NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
}

int main() {
    srand(time(0));
    int bullet = rand() % 6;
    int chamber = rand() % 6;
    if (bullet == chamber) bsod();
    else printf("you survived, the bullet was in: %i, you spun: %i", bullet, chamber);
    Sleep(1000);
    return 0;
}
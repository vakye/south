
#include "shared.h"
#include "shared.c"

#include "uefi.h"

EFI_STATUS EFIAPI BootUEFI(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    (void) ImageHandle;

    EFI_SIMPLE_TEXT_INPUT_PROTOCOL*     ConIn  = SystemTable->ConIn;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*    ConOut = SystemTable->ConOut;

    EFI_RUNTIME_SERVICES* RuntimeServices = SystemTable->RuntimeServices;

    ConOut->ClearScreen(ConOut);
    ConOut->OutputString(ConOut, L"Hello, world!\r\n");
    ConOut->OutputString(ConOut, L"Press any key to shutdown\r\n");

    EFI_INPUT_KEY Key = {0};
    while (ConIn->ReadKeyStroke(ConIn, &Key) != EFI_SUCCESS);

    RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, 0);

    return (EFI_SUCCESS);
}

void* memcpy(void* DestInit, const void* SourceInit, usize Size)
{
    u8* Dest = (u8*)DestInit;
    u8* Source = (u8*)SourceInit;

    while (Size--)
        *Dest++ = *Source++;

    return (DestInit);
}

void* memset(void* DestInit, s32 Byte, usize Size)
{
    u8* Dest = (u8*)DestInit;

    while (Size--)
        *Dest++ = (u8)Byte;

    return (DestInit);
}


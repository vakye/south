
#include "shared.h"
#include "shared.c"

#include "kernel.h"
#include "kernel.c"

#include "uefi.h"

local void UEFIError(
    EFI_SYSTEM_TABLE*                   SystemTable,
    CHAR16*                             Message
)
{
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL*     ConIn           = SystemTable->ConIn;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*    ConOut          = SystemTable->ConOut;
    EFI_RUNTIME_SERVICES*               RuntimeServices = SystemTable->RuntimeServices;

    ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(EFI_WHITE, EFI_BLACK));
    ConOut->OutputString(ConOut, L"[");
   
    ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(EFI_LIGHTRED, EFI_BLACK));
    ConOut->OutputString(ConOut, L"ERROR");
    
    ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(EFI_WHITE, EFI_BLACK));
    ConOut->OutputString(ConOut, L"]: ");
    ConOut->OutputString(ConOut, Message);
    ConOut->OutputString(ConOut, L"\r\n");
    ConOut->OutputString(ConOut, L"Press any key to shutdown\r\n");

    EFI_INPUT_KEY Key = {0};
    while (ConIn->ReadKeyStroke(ConIn, &Key) != EFI_SUCCESS);

    RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, 0);
}

EFI_STATUS EFIAPI UEFIBoot(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    (void) ImageHandle;

    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*    ConOut          = SystemTable->ConOut;
    EFI_BOOT_SERVICES*                  BootServices    = SystemTable->BootServices;

    ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(EFI_WHITE, EFI_BLACK));
    ConOut->ClearScreen(ConOut);

    usize MemoryMapSize     = 0;
    void* MemoryMap         = 0;
    usize MemoryMapKey      = 0;
    usize DescriptorSize    = 0;
    u32   DescriptorVersion = 0;

    for (;;)
    {
        EFI_STATUS Status = BootServices->GetMemoryMap(
            &MemoryMapSize,
            MemoryMap,
            &MemoryMapKey,
            &DescriptorSize,
            &DescriptorVersion
        );

        if (Status == EFI_SUCCESS)
        {
            break;
        }
        else if (Status == EFI_BUFFER_TOO_SMALL)
        {
            usize NewSize = MemoryMapSize + 4*DescriptorSize;

            if (MemoryMap)
            {
                EFI_STATUS FreeStatus = BootServices->FreePool(
                    MemoryMap
                );

                if (FreeStatus == EFI_INVALID_PARAMETER)
                {
                    UEFIError(SystemTable, L"Invalid parameter passed to BootServices->FreePool().");
                }
                else if (FreeStatus != EFI_SUCCESS)
                {
                    UEFIError(SystemTable, L"Unknown error in BootServices->FreePool().");
                }
            }

            EFI_STATUS AllocateStatus = BootServices->AllocatePool(
                EfiLoaderData,
                NewSize,
                &MemoryMap
            );

            if (AllocateStatus == EFI_OUT_OF_RESOURCES)
            {
                UEFIError(SystemTable, L"Unable to allocate memory map due to insufficient pool memory.");
            }
            else if (AllocateStatus == EFI_INVALID_PARAMETER)
            {
                UEFIError(SystemTable, L"Invalid parameter passed to BootServices->AllocatePool().");
            }
            else if (AllocateStatus != EFI_SUCCESS)
            {
                UEFIError(SystemTable, L"Unknown error in BootServices->AllocatePool().");
            }
        }
        else if (Status == EFI_INVALID_PARAMETER)
        {
            UEFIError(SystemTable, L"Invalid parameter passed to BootServices->GetMemoryMap().");
        }
        else
        {
            UEFIError(SystemTable, L"Unknown error in BootServices->GetMemoryMap().");
        }
    }

    EFI_STATUS ExitStatus = BootServices->ExitBootServices(
        ImageHandle,
        MemoryMapKey
    );

    if (ExitStatus == EFI_INVALID_PARAMETER)
    {
        UEFIError(SystemTable, L"Invalid parameter passed to BootServices->ExitBootServices().");
    }
    else if (ExitStatus != EFI_SUCCESS)
    {
        UEFIError(SystemTable, L"Unknown error in BootServices->ExitBootServices().");
    }

    KernelEntry();

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


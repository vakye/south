
#pragma once

typedef b8          BOOLEAN;

typedef s8          INT8;
typedef s16         INT16;
typedef s32         INT32;
typedef s64         INT64;
typedef ssize       INTN;

typedef u8          UINT8;
typedef u16         UINT16;
typedef u32         UINT32;
typedef u64         UINT64;
typedef usize       UINTN;

typedef UINT8       CHAR8;
typedef UINT16      CHAR16;

typedef void        VOID;

typedef UINT64      EFI_PHYSICAL_ADDRESS;
typedef UINT64      EFI_VIRTUAL_ADDRESS;

typedef struct
{
    UINT32 Part1;
    UINT16 Part2;
    UINT16 Part3;
    UINT8  Part4[6];
} GUID;

typedef GUID EFI_GUID;

typedef UINTN   EFI_STATUS;
typedef void*   EFI_HANDLE;
typedef VOID*   EFI_EVENT;
typedef UINT64  EFI_LBA;
typedef UINTN   EFI_TPL;

typedef struct
{
    UINT8 Addr[32];
} EFI_MAC_ADDRESS;

typedef struct
{
    UINT8 Addr[4];
} EFI_IPv4_ADDRESS;

typedef struct
{
    UINT8 Addr[16];
} EFI_IPv6_ADDRESS;

typedef struct
{
    UINT8 Addr[16];
} EFI_IP_ADDRESS;

#define EFIAPI __attribute__((ms_abi))

#define IN
#define OUT
#define CONST const

#define EFI_DEFINE_STATUS(A)        (((EFI_STATUS)(1) << (sizeof(EFI_STATUS)*8 - 1)) | (A))

#define EFI_SUCCESS                 (0)
#define EFI_LOAD_ERROR              EFI_DEFINE_STATUS( 1)
#define EFI_INVALID_PARAMETER       EFI_DEFINE_STATUS( 2)
#define EFI_UNSUPPORTED             EFI_DEFINE_STATUS( 3)
#define EFI_BAD_BUFFER_SIZE         EFI_DEFINE_STATUS( 4)
#define EFI_BUFFER_TOO_SMALL        EFI_DEFINE_STATUS( 5)
#define EFI_NOT_READY               EFI_DEFINE_STATUS( 6)
#define EFI_DEVICE_ERROR            EFI_DEFINE_STATUS( 7)
#define EFI_WRITE_PROTECTED         EFI_DEFINE_STATUS( 8)
#define EFI_OUT_OF_RESOURCES        EFI_DEFINE_STATUS( 9)
#define EFI_VOLUME_CORRUPTED        EFI_DEFINE_STATUS(10)
#define EFI_VOLUME_FULL             EFI_DEFINE_STATUS(11)
#define EFI_NO_MEDIA                EFI_DEFINE_STATUS(12)
#define EFI_MEDIA_CHANGED           EFI_DEFINE_STATUS(13)
#define EFI_NOT_FOUND               EFI_DEFINE_STATUS(14)
#define EFI_ACCESS_DENIED           EFI_DEFINE_STATUS(15)
#define EFI_NO_RESPONSE             EFI_DEFINE_STATUS(16)
#define EFI_NO_MAPPING              EFI_DEFINE_STATUS(17)
#define EFI_TIMEOUT                 EFI_DEFINE_STATUS(18)
#define EFI_NOT_STARTED             EFI_DEFINE_STATUS(19)
#define EFI_ALREADY_STARTED         EFI_DEFINE_STATUS(20)
#define EFI_ABORTED                 EFI_DEFINE_STATUS(21)
#define EFI_ICMP_ERROR              EFI_DEFINE_STATUS(22)
#define EFI_TFTP_ERROR              EFI_DEFINE_STATUS(23)
#define EFI_PROTOCOL_ERROR          EFI_DEFINE_STATUS(24)
#define EFI_IMCOMPATIBLE_VERSION    EFI_DEFINE_STATUS(25)
#define EFI_SECURITY_VIOLATION      EFI_DEFINE_STATUS(26)
#define EFI_CRC_ERROR               EFI_DEFINE_STATUS(27)
#define EFI_END_OF_MEDIA            EFI_DEFINE_STATUS(28)
#define EFI_END_OF_FILE             EFI_DEFINE_STATUS(31)
#define EFI_INVALID_LANGUAGE        EFI_DEFINE_STATUS(32)
#define EFI_COMPROMISED_DATA        EFI_DEFINE_STATUS(33)
#define EFI_IP_ADDRESS_CONFLICT     EFI_DEFINE_STATUS(34)
#define EFI_HTTP_ERROR              EFI_DEFINE_STATUS(35)

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
    {0x387477c2,0x69c7,0x11d2,\
    {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct
{
    INT32                   MaxMode;
    INT32                   Mode;
    INT32                   Attribute;
    INT32                   CursorColumn;
    INT32                   CursorRow;
    BOOLEAN                 CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef EFI_STATUS (EFIAPI *EFI_TEXT_RESET)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*         This,
    IN BOOLEAN                                  ExtendedVerification
);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*         This,
    IN CHAR16*                                  String
);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_TEST_STRING)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*         This,
    IN CHAR16*                                  String
);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_QUERY_MODE)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*         This,
    IN UINTN                                    ModeNumber,
    OUT UINTN*                                  Columns,
    OUT UINTN*                                  Rows
);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_MODE)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*         This,
    IN UINTN                                    ModeNumber
);

#define EFI_BLACK                               0x00
#define EFI_BLUE                                0x01
#define EFI_GREEN                               0x02
#define EFI_CYAN                                0x03
#define EFI_RED                                 0x04
#define EFI_MAGENTA                             0x05
#define EFI_BROWN                               0x06
#define EFI_LIGHTGRAY                           0x07
#define EFI_BRIGHT                              0x08
#define EFI_DARKGRAY                            0x08
#define EFI_LIGHTBLUE                           0x09
#define EFI_LIGHTGREEN                          0x0A
#define EFI_LIGHTCYAN                           0x0B
#define EFI_LIGHTRED                            0x0C
#define EFI_LIGHTMAGENTA                        0x0D
#define EFI_YELLOW                              0x0E
#define EFI_WHITE                               0x0F

#define EFI_TEXT_ATTR(Foreground, Background) ((Foreground) | ((Background) << 4))

typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_ATTRIBUTE)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*         This,
    IN UINTN                                    Attribute
);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_CLEAR_SCREEN)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*         This
);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_CURSOR_POSITION)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*         This,
    IN UINTN                                    Column,
    IN UINTN                                    Row
);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_ENABLE_CURSOR)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*         This,
    IN BOOLEAN                                  Visible
);

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    EFI_TEXT_RESET                              Reset;
    EFI_TEXT_STRING                             OutputString;
    EFI_TEXT_TEST_STRING                        TestString;
    EFI_TEXT_QUERY_MODE                         QueryMode;
    EFI_TEXT_SET_MODE                           SetMode;
    EFI_TEXT_SET_ATTRIBUTE                      SetAttribute;
    EFI_TEXT_CLEAR_SCREEN                       ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION                SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR                      EnableCursor;
    SIMPLE_TEXT_OUTPUT_MODE*                    Mode;
};

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
    {0x387477c1,0x69c7,0x11d2,\
    {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_INPUT_RESET)(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL*          This,
    IN BOOLEAN                                  ExtendedVerification
);

typedef struct
{
    UINT16                  ScanCode;
    CHAR16                  UnicodeChar;
} EFI_INPUT_KEY;

typedef EFI_STATUS (EFIAPI *EFI_INPUT_READ_KEY)(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL*          This,
    OUT EFI_INPUT_KEY*                          Key
);

struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
    EFI_INPUT_RESET                             Reset;
    EFI_INPUT_READ_KEY                          ReadKeyStroke;
    EFI_EVENT                                   WaitForKey;
};

#define EFI_DEVICE_PATH_PROTOCOL_GUID \
    {0x09576e91,0x6d3f,0x11d2,\
    {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct _EFI_DEVICE_PATH_PROTOCOL
{
    UINT8               Type;
    UINT8               SubType;
    UINT8               Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct
{
    UINT32                                      Type;
    EFI_PHYSICAL_ADDRESS                        PhysicalStart;
    EFI_VIRTUAL_ADDRESS                         VirtualStart;
    UINT64                                      NumberOfPages;
    UINT64                                      Attribute;
} EFI_MEMORY_DESCRIPTOR;

#define EFI_MEMORY_UC               0x0000000000000001
#define EFI_MEMORY_WC               0x0000000000000002
#define EFI_MEMORY_WT               0x0000000000000004
#define EFI_MEMORY_WB               0x0000000000000008
#define EFI_MEMORY_UCE              0x0000000000000010
#define EFI_MEMORY_WP               0x0000000000001000
#define EFI_MEMORY_RP               0x0000000000002000
#define EFI_MEMORY_XP               0x0000000000004000
#define EFI_MEMORY_NV               0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE    0x0000000000010000
#define EFI_MEMORY_RO               0x0000000000020000
#define EFI_MEMORY_SP               0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO       0x0000000000080000
#define EFI_MEMORY_RUNTIME          0x8000000000000000
#define EFI_MEMORY_ISA_VALID        0x4000000000000000
#define EFI_MEMORY_ISA_MASK         0x0FFFF00000000000

#define EFI_MEMORY_DESCRIPTOR_VERSION   (1)

typedef struct
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef struct
{
    UINT16                                      Year;
    UINT8                                       Month;
    UINT8                                       Day;
    UINT8                                       Hour;
    UINT8                                       Minute;
    UINT8                                       Second;
    UINT8                                       Pad1;
    UINT32                                      Nanosecond;
    INT16                                       TimeZone;
    UINT8                                       Daylight;
    UINT8                                       Pad2;
} EFI_TIME;

#define EFI_TIME_ADJUST_DAYLIGHT                (0x01)
#define EFI_TIME_IN_DAYLIGHT                    (0x02)
#define EFI_UNSPECIFIED_TIMEZONE                (0x07FF)

typedef struct
{
    UINT32                                      Resolution;
    UINT32                                      Accuracy;
    BOOLEAN                                     SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef EFI_STATUS (EFIAPI *EFI_GET_TIME)(
    OUT EFI_TIME*                               Time,
    OUT EFI_TIME_CAPABILITIES*                  Capabilities
);

typedef EFI_STATUS (EFIAPI *EFI_SET_TIME)(
    IN EFI_TIME*                                Time
);

typedef EFI_STATUS (EFIAPI *EFI_GET_WAKEUP_TIME)(
    OUT BOOLEAN*                                Enabled,
    OUT BOOLEAN*                                Pending,
    OUT EFI_TIME*                               Time
);

typedef EFI_STATUS (EFIAPI *EFI_SET_WAKEUP_TIME)(
    IN BOOLEAN*                                 Enable,
    IN EFI_TIME*                                Time
);

typedef EFI_STATUS (EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP)(
    IN UINTN                                    MemoryMapSize,
    IN UINTN                                    DescriptorSize,
    IN UINT32                                   DescriptorVersion,
    IN EFI_MEMORY_DESCRIPTOR*                   VirtualMap
);

#define EFI_OPTIONAL_PTR (0x01)

typedef EFI_STATUS (EFIAPI *EFI_CONVERT_POINTER)(
    IN UINTN                                    DebugDisposition,
    IN VOID**                                   Address
);

#define EFI_VARIABLE_NON_VOLATILE                           0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                     0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS                         0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                  0x00000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS             0x00000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS  0x00000020
#define EFI_VARIABLE_APPEND_WRITE                           0x00000040
#define EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS          0x00000080

typedef EFI_STATUS (EFIAPI *EFI_GET_VARIABLE)(
    IN CHAR16*                                  VariableName,
    IN EFI_GUID*                                VendorGuid,
    OUT UINT32*                                 Attributes,
    IN OUT UINTN*                               DataSize,
    OUT VOID*                                   Data
);

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_VARIABLE_NAME)(
    IN OUT UINTN*                               VariableNameSize,
    IN OUT CHAR16*                              VariableName,
    IN OUT EFI_GUID*                            VendorGuid
);

typedef EFI_STATUS (EFIAPI *EFI_SET_VARIABLE)(
    IN CHAR16*                                  VariableName,
    IN EFI_GUID*                                VendorGuid,
    IN UINT32                                   Attributes,
    IN UINTN                                    DataSize,
    IN VOID*                                    Data
);

typedef EFI_STATUS (EFIAPI *EFI_QUERY_VARIABLE_INFO)(
    IN UINT32                                   Attributes,
    OUT UINT64*                                 MaximumVariableStorageSize,
    OUT UINT64*                                 RemainingVariableStorageSize,
    OUT UINT64*                                 MaximumVariableSize
);

typedef enum
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef EFI_STATUS (EFIAPI *EFI_RESET_SYSTEM)(
    IN EFI_RESET_TYPE                           ResetType,
    IN EFI_STATUS                               ResetStatus,
    IN UINTN                                    DataSize,
    IN VOID*                                    ResetData
);

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT)(
    OUT UINT32*                                 HighCount
);

typedef struct
{
    UINT64 Length;
    union
    {
        EFI_PHYSICAL_ADDRESS        DataBlock;
        EFI_PHYSICAL_ADDRESS        ContinuationPointer;
    } Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET 0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET 0x00040000

typedef struct
{
    EFI_GUID                        CapsuleGuid;
    UINT32                          HeaderSize;
    UINT32                          Flags;
    UINT32                          CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef struct
{
    UINT32                          CapsuleArrayNumber;
    VOID*                           CapsulePtr[1];
} EFI_CAPSULE_TABLE;

typedef EFI_STATUS (EFIAPI *EFI_UPDATE_CAPSULE)(
    IN EFI_CAPSULE_HEADER**                     CapsuleHeaderArray,
    IN UINTN                                    CapsuleCount,
    IN EFI_PHYSICAL_ADDRESS                     ScatterGatherList
);

typedef EFI_STATUS (EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES)(
    IN EFI_CAPSULE_HEADER**                     CapsuleHeaderArray,
    IN UINTN                                    CapsuleCount,
    OUT UINT64*                                 MaximumCapsuleSize,
    OUT EFI_RESET_TYPE*                         ResetType
);

typedef struct
{
    EFI_TABLE_HEADER                            Hdr;

    EFI_GET_TIME                                GetTime;
    EFI_SET_TIME                                SetTime;
    EFI_GET_WAKEUP_TIME                         GetWakeupTime;
    EFI_SET_WAKEUP_TIME                         SetWakeupTime;

    EFI_SET_VIRTUAL_ADDRESS_MAP                 SetVirtualAddressMap;
    EFI_CONVERT_POINTER                         ConvertPointer;

    EFI_GET_VARIABLE                            GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME                  GetNextVariableName;
    EFI_SET_VARIABLE                            SetVariable;

    EFI_GET_NEXT_HIGH_MONO_COUNT                GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM                            ResetSystem;

    EFI_UPDATE_CAPSULE                          UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES              QueryCapsuleCapabilities;

    EFI_QUERY_VARIABLE_INFO                     QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

#define TPL_APPLICATION             (4)
#define TPL_CALLBACK                (8)
#define TPL_NOTIFY                  (16)
#define TPL_HIGH_LEVEL              (31)

#define EVT_TIMER                               0x80000000
#define EVT_RUNTIME                             0x40000000

#define EVT_NOTIFY_WAIT                         0x00000100
#define EVT_NOTIFY_SIGNAL                       0x00000200

#define EVT_SIGNAL_EXIT_BOOT_SERVICES           0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE       0x60000202

typedef VOID (EFIAPI *EFI_EVENT_NOTIFY)(
    IN EFI_EVENT                                Event,
    IN VOID*                                    Context
);

typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT)(
    IN UINT32                                   Type,
    IN EFI_TPL                                  NotifyTpl,
    IN EFI_EVENT_NOTIFY                         NotifyFunction,
    IN VOID*                                    NotifyContext,
    OUT EFI_EVENT*                              Event
);

#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES \
{0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37,\
0xba, 0xa2, 0xdf}}

#define EFI_EVENT_GROUP_BEFORE_EXIT_BOOT_SERVICES \
{ 0x8be0e274, 0x3970, 0x4b44, { 0x80, 0xc5, 0x1a, 0xb9, 0x50, 0x2f, 0x3b, 0xfc } }

#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE \
{0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc,\
0xc2, 0x51, 0x96}

#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE \
{0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, \
0xf0, 0xd7, 0xab}

#define EFI_EVENT_GROUP_READY_TO_BOOT \
{0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde,\
0xe5,0xd, 0x2b}

#define EFI_EVENT_GROUP_AFTER_READY_TO_BOOT \
{ 0x3a2a00ad, 0x98b9, 0x4cdf, { 0xa4, 0x78, 0x70, 0x27, 0x77, \
0xf1, 0xc1, 0xb } }

#define EFI_EVENT_GROUP_RESET_SYSTEM \
{ 0x62da6a56, 0x13fb, 0x485a, { 0xa8, 0xda, 0xa3, 0xdd, 0x79, 0x12, 0xcb, 0x6b \
} }

#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES \
{0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37,\
0xba, 0xa2, 0xdf}}

#define EFI_EVENT_GROUP_BEFORE_EXIT_BOOT_SERVICES \
{ 0x8be0e274, 0x3970, 0x4b44, { 0x80, 0xc5, 0x1a, 0xb9, 0x50, 0x2f, 0x3b, 0xfc } }

#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE \
{0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc,\
0xc2, 0x51, 0x96}

#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE \
{0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, \
0xf0, 0xd7, 0xab}

#define EFI_EVENT_GROUP_READY_TO_BOOT \
{0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde,\
0xe5,0xd, 0x2b}

#define EFI_EVENT_GROUP_AFTER_READY_TO_BOOT \
{ 0x3a2a00ad, 0x98b9, 0x4cdf, { 0xa4, 0x78, 0x70, 0x27, 0x77, \
0xf1, 0xc1, 0xb } }

#define EFI_EVENT_GROUP_RESET_SYSTEM \
{ 0x62da6a56, 0x13fb, 0x485a, { 0xa8, 0xda, 0xa3, 0xdd, 0x79, 0x12, 0xcb, 0x6b \
} }

typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT_EX)(
    IN UINT32                                   Type,
    IN EFI_TPL                                  NotifyTpl,
    IN EFI_EVENT_NOTIFY                         NotifyFunction,
    IN CONST VOID*                              NotifyContext,
    IN CONST EFI_GUID*                          EventGroup,
    OUT EFI_EVENT*                              Event
);

typedef EFI_STATUS (EFIAPI *EFI_CLOSE_EVENT)(
    IN EFI_EVENT                                Event
);

typedef EFI_STATUS (EFIAPI *EFI_SIGNAL_EVENT)(
    IN EFI_EVENT                                Event
);

typedef EFI_STATUS (EFIAPI *EFI_WAIT_FOR_EVENT)(
    IN UINTN                                    NumberOfEvents,
    IN EFI_EVENT*                               Event,
    OUT UINTN*                                  Index
);

typedef EFI_STATUS (EFIAPI *EFI_CHECK_EVENT)(
    IN EFI_EVENT                                Event
);

typedef enum
{
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} EFI_TIMER_DELAY;

typedef EFI_STATUS (EFIAPI *EFI_SET_TIMER)(
    IN EFI_EVENT                                Event,
    IN EFI_TIMER_DELAY                          Type,
    IN UINT64                                   TriggerTime
);

typedef EFI_TPL (EFIAPI *EFI_RAISE_TPL)(
    IN EFI_TPL                                  NewTpl
);

typedef void (EFIAPI *EFI_RESTORE_TPL)(
    IN EFI_TPL                                  OldTpl
);

typedef enum
{
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType,
} EFI_ALLOCATE_TYPE;

typedef enum
{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType,
} EFI_MEMORY_TYPE;

typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_PAGES)(
    IN EFI_ALLOCATE_TYPE                        Type,
    IN EFI_MEMORY_TYPE                          MemoryType,
    IN UINTN                                    Pages,
    IN OUT EFI_PHYSICAL_ADDRESS*                Memory
);

typedef EFI_STATUS (EFIAPI *EFI_FREE_PAGES)(
    IN EFI_PHYSICAL_ADDRESS                     Memory,
    IN UINTN                                    Pages
);

typedef EFI_STATUS (EFIAPI *EFI_GET_MEMORY_MAP)(
    IN OUT UINTN*                               MemoryMapSize,
    OUT EFI_MEMORY_DESCRIPTOR*                  MemoryMap,
    OUT UINTN*                                  MapKey,
    OUT UINTN*                                  DescriptorSize,
    OUT UINT32*                                 DescriptorVersion
);

typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_POOL)(
    IN EFI_MEMORY_TYPE                          PoolType,
    IN UINTN                                    Size,
    OUT VOID**                                  Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_FREE_POOL)(
    IN VOID*                                    Buffer
);

typedef enum
{
    EFI_NATIVE_INTERFACE,
} EFI_INTERFACE_TYPE;

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE)(
    IN OUT EFI_HANDLE*                          Handle,
    IN EFI_GUID*                                Protocol,
    IN EFI_INTERFACE_TYPE                       InterfaceType,
    IN VOID*                                    Interface
);

typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE)(
    IN EFI_HANDLE                               Handle,
    IN EFI_GUID*                                Protocol,
    IN VOID*                                    Interface
);

typedef EFI_STATUS (EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE)(
    IN EFI_HANDLE                               Handle,
    IN EFI_GUID*                                Protocol,
    IN VOID*                                    OldInterface,
    IN VOID*                                    NewInterface
);

typedef EFI_STATUS (EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY)(
    IN EFI_GUID*                                Protocol,
    IN EFI_EVENT                                Event,
    OUT VOID**                                  Registration
);

typedef enum
{
    AllHandles,
    ByRegisterNotify,
    ByProtocol,
} EFI_LOCATE_SEARCH_TYPE;

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE)(
    IN EFI_LOCATE_SEARCH_TYPE                   SearchType,
    IN EFI_GUID*                                Protocol,
    IN VOID*                                    SearchKey,
    IN OUT UINTN*                               BufferSize,
    OUT EFI_HANDLE*                             Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_HANDLE_PROTOCOL)(
    IN EFI_HANDLE                               Handle,
    IN EFI_GUID*                                Protocol,
    OUT VOID**                                  Interface
);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_DEVICE_PATH)(
    IN EFI_GUID*                                Protocol,
    IN OUT EFI_DEVICE_PATH_PROTOCOL**           DevicePath,
    OUT EFI_HANDLE*                             Device
);

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL    0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL          0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL         0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER   0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER             0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE             0x00000020

typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL)(
    IN EFI_HANDLE                               Handle,
    IN EFI_GUID*                                Protocol,
    OUT VOID**                                  Interface,
    IN EFI_HANDLE                               AgentHandle,
    IN EFI_HANDLE                               ControllerHandle,
    IN UINT32                                   Attributes
);

typedef EFI_STATUS (EFIAPI *EFI_CLOSE_PROTOCOL)(
    IN EFI_HANDLE                               Handle,
    IN EFI_GUID*                                Protocol,
    IN EFI_HANDLE                               AgentHandle,
    IN EFI_HANDLE                               ControllerHandle
);

typedef struct
{
    EFI_HANDLE              AgentHandle;
    EFI_HANDLE              ControllerHandle;
    UINT32                  Attributes;
    UINT32                  OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION)(
    IN EFI_HANDLE                               Handle,
    IN EFI_GUID*                                PROTOCOL,
    OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY**   EntryBuffer,
    OUT UINTN*                                  EntryCount
);

typedef EFI_STATUS (EFIAPI *EFI_CONNECT_CONTROLLER)(
    IN EFI_HANDLE                               ControllerHandle,
    IN EFI_HANDLE*                              DriverImageHandle,
    IN EFI_DEVICE_PATH_PROTOCOL*                RemainingDevicePath,
    IN BOOLEAN                                  Recursive
);

typedef EFI_STATUS (EFIAPI *EFI_DISCONNECT_CONTROLLER)(
    IN EFI_HANDLE                               ControllerHandle,
    IN EFI_HANDLE                               DriverImageHandle,
    IN EFI_HANDLE                               ChildHandle
);

typedef EFI_STATUS (EFIAPI *EFI_PROTOCOLS_PER_HANDLE)(
    IN EFI_HANDLE                               Handle,
    OUT EFI_GUID***                             ProtocolBuffer,
    OUT UINTN*                                  ProtocolBufferCount
);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE_BUFFER)(
    IN EFI_LOCATE_SEARCH_TYPE                   SearchType,
    IN EFI_GUID*                                Protocol,
    IN VOID*                                    SearchKey,
    OUT UINTN*                                  NoHandles,
    OUT EFI_HANDLE**                            Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_PROTOCOL)(
    IN EFI_GUID*                                Protocol,
    IN VOID*                                    Registration,
    OUT VOID**                                  Interface
);

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    IN OUT EFI_HANDLE*                          Handle,
    ...
);

typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    IN OUT EFI_HANDLE*                          Handle,
    ...
);

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_LOAD)(
    IN BOOLEAN                                  BootPolicy,
    IN EFI_HANDLE                               ParentImageHandle,
    IN EFI_DEVICE_PATH_PROTOCOL*                DevicePath,
    IN VOID*                                    SourceBuffer,
    IN UINTN                                    SourceSize,
    OUT EFI_HANDLE*                             ImageHandle
);

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_START)(
    IN EFI_HANDLE                               ImageHandle,
    OUT UINTN*                                  ExitDataSize,
    OUT CHAR16**                                ExitData
);

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_UNLOAD)(
    IN EFI_HANDLE                               ImageHandle
);

typedef EFI_STATUS (EFIAPI *EFI_EXIT)(
    IN EFI_HANDLE                               ImageHandle,
    IN EFI_STATUS                               ExitStatus,
    IN UINTN                                    ExitDataSize,
    IN CHAR16*                                  ExitData
);

typedef EFI_STATUS (EFIAPI *EFI_EXIT_BOOT_SERVICES)(
    IN EFI_HANDLE                               ImageHandle,
    IN UINTN                                    MapKey
);

typedef EFI_STATUS (EFIAPI *EFI_SET_WATCHDOG_TIMER)(
    IN UINTN                                    Timeout,
    IN UINT64                                   WatchdogCode,
    IN UINTN                                    DataSize,
    IN CHAR16*                                  WatchdogData
);

typedef EFI_STATUS (EFIAPI *EFI_STALL)(
    IN UINTN                                    Microseconds
);

typedef VOID (EFIAPI *EFI_COPY_MEM)(
    IN VOID*                                    Destination,
    IN VOID*                                    Source,
    IN UINTN                                    Length
);

typedef VOID (EFIAPI *EFI_SET_MEM)(
    IN VOID*                                    Buffer,
    IN UINTN                                    Size,
    IN UINT8                                    Value
);

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT)(
    OUT UINT64*                                 Count
);

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE)(
    IN EFI_GUID*                                Guid,
    IN VOID*                                    Table
);

typedef EFI_STATUS (EFIAPI *EFI_CALCULATE_CRC32)(
    IN VOID*                                    Data,
    IN UINTN                                    DataSize,
    OUT UINT32*                                 Crc32
);

typedef struct
{
    EFI_TABLE_HEADER                            Hdr;

    EFI_RAISE_TPL                               RaiseTPL;
    EFI_RESTORE_TPL                             RestoreTPL;

    EFI_ALLOCATE_PAGES                          AllocatePages;
    EFI_FREE_PAGES                              FreePages;
    EFI_GET_MEMORY_MAP                          GetMemoryMap;
    EFI_ALLOCATE_POOL                           AllocatePool;
    EFI_FREE_POOL                               FreePool;

    EFI_CREATE_EVENT                            CreateEvent;
    EFI_SET_TIMER                               SetTimer;
    EFI_WAIT_FOR_EVENT                          WaitForEvent;
    EFI_SIGNAL_EVENT                            SignalEvent;
    EFI_CLOSE_EVENT                             CloseEvent;
    EFI_CHECK_EVENT                             CheckEvent;

    EFI_INSTALL_PROTOCOL_INTERFACE              InstallProtocolInterface;
    EFI_REINSTALL_PROTOCOL_INTERFACE            ReinstallProtocolInterface;
    EFI_UNINSTALL_PROTOCOL_INTERFACE            UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL                         HandleProtocol;
    VOID*                                       Reserved;
    EFI_REGISTER_PROTOCOL_NOTIFY                RegisterProtocolNotify;
    EFI_LOCATE_HANDLE                           LocateHandle;
    EFI_LOCATE_DEVICE_PATH                      LocateDevicePath;
    EFI_INSTALL_CONFIGURATION_TABLE             InstallConfigurationTable;

    EFI_IMAGE_LOAD                              LoadImage;
    EFI_IMAGE_START                             StartImage;
    EFI_EXIT                                    Exit;
    EFI_IMAGE_UNLOAD                            UnloadImage;
    EFI_EXIT_BOOT_SERVICES                      ExitBootServices;

    EFI_GET_NEXT_MONOTONIC_COUNT                GetNextMonotonicCount;
    EFI_STALL                                   Stall;
    EFI_SET_WATCHDOG_TIMER                      SetWatchdogTimer;

    EFI_CONNECT_CONTROLLER                      ConnectController;
    EFI_DISCONNECT_CONTROLLER                   DisconnectController;

    EFI_OPEN_PROTOCOL                           OpenProtocol;
    EFI_CLOSE_PROTOCOL                          CloseProtocol;
    EFI_OPEN_PROTOCOL_INFORMATION               OpenProtocolInformation;

    EFI_PROTOCOLS_PER_HANDLE                    ProtocolsPerHandle;
    EFI_LOCATE_HANDLE_BUFFER                    LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL                         LocateProtocol;

    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES    InstallMultipleProtocolInterfaces;
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  UninstallMultipleProtocolInterfaces;

    EFI_CALCULATE_CRC32                         CalculateCrc32;

    EFI_COPY_MEM                                CopyMem;
    EFI_SET_MEM                                 SetMem;
    EFI_CREATE_EVENT_EX                         CreateEventEx;
} EFI_BOOT_SERVICES;

typedef struct
{
    EFI_GUID                                    VendorGuid;
    VOID*                                       VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef struct
{
    EFI_TABLE_HEADER                            Hdr;
    CHAR16*                                     FirmwareVendor;
    UINT32                                      FirmwareRevision;
    EFI_HANDLE                                  ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL*             ConIn;
    EFI_HANDLE                                  ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*            ConOut;
    EFI_HANDLE                                  StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*            StdErr;
    EFI_RUNTIME_SERVICES*                       RuntimeServices;
    EFI_BOOT_SERVICES*                          BootServices;
    UINTN                                       NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE*                    ConfigurationTable;
} EFI_SYSTEM_TABLE;


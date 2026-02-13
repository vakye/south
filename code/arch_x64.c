
#pragma pack(push, 1)

typedef struct
{
    u16 Limit0;
    u16 Base0;
    u8  Base1;
    u8  Access;
    u8  Limit1AndFlags;
    u8  Base2;
} x64_gdt_entry;

typedef struct
{
    u16 Limit;
    u64 Address;
} x64_gdt_register;

typedef u64 x64_page_flags;

#define x64_PageFlag_Present        ((usize)(1) << 0)
#define x64_PageFlag_ReadWrite      ((usize)(1) << 1)
#define x64_PageFlag_UserAccessible ((usize)(1) << 2)
#define x64_PageFlag_WriteThrough   ((usize)(1) << 3)
#define x64_PageFlag_CacheDisable   ((usize)(1) << 4)
#define x64_PageFlag_Accessed       ((usize)(1) << 5)
#define x64_PageFlag_Dirty          ((usize)(1) << 6)
#define x64_PageFlag_AttributeTable ((usize)(1) << 7)
#define x64_PageFlag_Global         ((usize)(1) << 9)
#define x64_PageFlag_ExecuteDisable ((usize)(1) << 63)

#define x64_PageAddressMask     (0x01FFFFFFFFFFF000)

struct arch_page_map
{
    AlignAs(4096) u64 Entries[512];
};

#pragma pack(pop)

local void ArchSetup(void)
{
    // NOTE(vak): Clear interrupts

    __asm volatile ("cli");

    // NOTE(vak): Setup GDT

    x64_gdt_entry GDT[] =
    {
        {0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00}, // NOTE(vak): NULL
        {0x0000, 0x0000, 0x00, 0x9A, 0xA0, 0x00}, // NOTE(vak): Code
        {0x0000, 0x0000, 0x00, 0x92, 0xA0, 0x00}, // NOTE(vak): Data
    };

    x64_gdt_register GDTR =
    {
        .Limit      = sizeof(GDT) - 1,
        .Address    = (usize)GDT,
    };

    __asm volatile
    (
        "   lgdtq %0\n"
        "   movq $DummyLabel, %%rax\n"
        "   push $0x08\n"
        "   push %%rax\n"
        "   lretq\n"
        "DummyLabel:\n"
        "    movw $0x10, %%ax\n"
        "    movw %%ax, %%ds\n"
        "    movw %%ax, %%es\n"
        "    movw %%ax, %%fs\n"
        "    movw %%ax, %%gs\n"
        "    movw %%ax, %%ss\n"
        : : "m"(GDTR) : "rax"
    );
}

local usize ArchGetPageSize(void)
{
    usize Result = KB(4);
    return (Result);
}

local arch_page_arena ArchPlacePageArena(void* Base, usize PageCount)
{
    arch_page_arena Result =
    {
        .Base      = Base,
        .PageCount = PageCount,
    };

    return (Result);
}

local void* ArchAllocatePage(arch_page_arena* Arena)
{
    void* Result = 0;

    if (Arena->PagesUsed < Arena->PageCount)
    {
        Result = (u8*)Arena->Base + Arena->PagesUsed * ArchGetPageSize();

        Arena->PagesUsed++;
    }

    return (Result);
}

local arch_page_map* ArchMakePageMap(arch_page_arena* Arena)
{
    arch_page_map* Map = ArchAllocatePage(Arena);
    ZeroStruct(Map);

    return (Map);
}

local arch_page_map* ArchAccessPageMap(arch_page_arena* Arena, arch_page_map* Map, usize EntryIndex)
{
    arch_page_map* Result = 0;

    if (Map && (EntryIndex < ArrayCount(Map->Entries)))
    {
        if ((Map->Entries[EntryIndex] & x64_PageFlag_Present) == 0)
        {
            arch_page_map* New   = ArchMakePageMap(Arena);
            x64_page_flags Flags = x64_PageFlag_Present | x64_PageFlag_ReadWrite;

            Map->Entries[EntryIndex] = (usize)(New) | Flags;
        }

        Result = (arch_page_map*)(Map->Entries[EntryIndex] & x64_PageAddressMask);
    }

    return (Result);
}

local void ArchMapPage(arch_page_arena* Arena, arch_page_map* Map, usize PhysicalAddress, usize VirtualAddress)
{
    usize PageSize = ArchGetPageSize();

    if (VirtualAddress  >= x64_PageAddressMask + PageSize) return;
    if (PhysicalAddress >= x64_PageAddressMask + PageSize) return;

    VirtualAddress  &= x64_PageAddressMask;
    PhysicalAddress &= x64_PageAddressMask;

    usize IndexPML4 = (VirtualAddress >> 39) & 0x1FF;
    usize IndexPDPT = (VirtualAddress >> 30) & 0x1FF;
    usize IndexPDT  = (VirtualAddress >> 21) & 0x1FF;
    usize IndexPT   = (VirtualAddress >> 12) & 0x1FF;

    arch_page_map* PML4 = Map;

    if (IndexPML4 >= ArrayCount(PML4->Entries))
        return;

    *(u32*)0x10000 = 0xDEADBEEF;

    arch_page_map* PDPT = ArchAccessPageMap(Arena, PML4, IndexPML4);
    arch_page_map* PDT  = ArchAccessPageMap(Arena, PDPT, IndexPDPT);
    arch_page_map* PT   = ArchAccessPageMap(Arena, PDT,  IndexPDT );

    x64_page_flags Flags = x64_PageFlag_Present | x64_PageFlag_ReadWrite;
    PT->Entries[IndexPT] = PhysicalAddress | Flags;
}

local void ArchUsePageMap(arch_page_map* Map)
{
    __asm volatile
    (
        "mov %0, %%cr3\n"
        : : "r"(Map)
    );
}

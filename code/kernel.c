
local page_arena CreatePageArena(memory_region Region)
{
    page_arena Result =
    {
        .Base      = Region.Base,
        .PageCount = Region.PageCount,
    };

    return (Result);
}

local void* AllocatePage(page_arena* Arena)
{
    void* Result = 0;

    if (Arena->PagesUsed < Arena->PageCount)
    {
        Result = (u8*)Arena->Base + (KB(4) * Arena->PagesUsed);

        Arena->PagesUsed++;
    }

    return (Result);
}

local b32 IsPageTableEntryPresent(page_table* Table, usize EntryIndex)
{
    u64 Entry = 0;

    if (Table && (EntryIndex < ArrayCount(Table->Entries)))
    {
        Entry = Table->Entries[EntryIndex];
    }

    b32 Result = ((Entry & PageFlag_Present) != 0);

    return (Result);
}

local page_table* AccessPageTable(page_arena* Arena, page_table* Table, usize EntryIndex)
{
    page_table* Result = 0;

    if (Table && (EntryIndex < ArrayCount(Table->Entries)))
    {
        if (!IsPageTableEntryPresent(Table, EntryIndex))
        {
            page_table* New = AllocatePage(Arena);
            ZeroStruct(New);

            usize Address = (usize)(New);

            Table->Entries[EntryIndex] = (Address|PageFlag_Present|PageFlag_ReadWrite);
        }

        Result = (page_table*)(Table->Entries[EntryIndex] & PageAddressMask);
    }

    return (Result);
}

local void IdentityMapPage(page_arena* Arena, page_table* PML4, usize Address)
{
    if (Address >= (PageAddressMask + KB(4)))
        return;

    Address &= PageAddressMask;

    usize IndexPML4 = (Address >> 39) & 0x1FF;
    usize IndexPDPT = (Address >> 30) & 0x1FF;
    usize IndexPDT  = (Address >> 21) & 0x1FF;
    usize IndexPT   = (Address >> 12) & 0x1FF;

    if (IndexPML4 >= ArrayCount(PML4->Entries))
        return;

    page_table* PDPT = AccessPageTable(Arena, PML4, IndexPML4);
    page_table* PDT  = AccessPageTable(Arena, PDPT, IndexPDPT);
    page_table* PT   = AccessPageTable(Arena, PDT,  IndexPDT );

    PT->Entries[IndexPT] = (Address|PageFlag_Present|PageFlag_ReadWrite);
}

local void KernelEntry(memory_region Region)
{
    ArchSetup();

    page_arena Arena = CreatePageArena(Region);
    page_table* PML4 = (page_table*)AllocatePage(&Arena);

    ZeroStruct(PML4);

    for (usize Address = 0; Address < GB(4); Address += KB(4))
    {
        IdentityMapPage(&Arena, PML4, Address);
    }

    ArchLoadPML4(PML4);

    for (;;);
}

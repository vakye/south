
local void KernelEntry(memory_region Region)
{
    ArchSetup();

    usize PageSize = ArchGetPageSize();

    arch_page_arena PageArena = ArchPlacePageArena(Region.Base, Region.PageCount);
    arch_page_map* PageMap = ArchMakePageMap(&PageArena);

    for (usize Address = 0; Address < GB(4); Address += PageSize)
    {
        usize Physical = Address;
        usize Virtual  = Address;

        ArchMapPage(&PageArena, PageMap, Physical, Virtual);
    }

    ArchUsePageMap(PageMap);

    for (;;);
}


#pragma once

typedef struct arch_page_map arch_page_map;

typedef struct
{
    void* Base;
    usize PagesUsed;
    usize PageCount;
} arch_page_arena;

local void            ArchSetup          (void);
local usize           ArchGetPageSize    (void);

local arch_page_arena ArchPlacePageArena (void* Base, usize PageCount);
local void*           ArchAllocatePage   (arch_page_arena* Arena);

local arch_page_map*  ArchMakePageMap    (arch_page_arena* Arena);
local void            ArchMapPage        (arch_page_arena* Arena, arch_page_map* Map, usize PhysicalAddress, usize VirtualAddress);
local void            ArchUsePageMap     (arch_page_map* Map);

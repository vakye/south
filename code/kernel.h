
#pragma once

typedef struct
{
    usize Base;
    usize PageCount;
} memory_region;

typedef struct
{
    usize Base;
    usize PageCount;
    usize PagesUsed;
} page_arena;

#pragma pack(push, 1)

typedef struct
{
    AlignAs(4096) u64 Entries[512];
} page_table;

#pragma pack(pop)

#define PageFlag_Present        ((usize)(1) << 0)
#define PageFlag_ReadWrite      ((usize)(1) << 1)
#define PageFlag_UserAccessible ((usize)(1) << 2)
#define PageFlag_WriteThrough   ((usize)(1) << 3)
#define PageFlag_CacheDisable   ((usize)(1) << 4)
#define PageFlag_Accessed       ((usize)(1) << 5)
#define PageFlag_Dirty          ((usize)(1) << 6)
#define PageFlag_AttributeTable ((usize)(1) << 7)
#define PageFlag_Global         ((usize)(1) << 9)
#define PageFlag_ExecuteDisable ((usize)(1) << 63)

#define PageAddressMask     (0x01FFFFFFFFFFF000)

local void KernelEntry(memory_region Region);

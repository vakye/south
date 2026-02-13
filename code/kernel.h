
typedef struct
{
    void* Base;
    usize PageCount;
} memory_region;

local void KernelEntry(memory_region Region);

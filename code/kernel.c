
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

#pragma pack(pop)

local void x64Setup(void)
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

    __asm volatile ("lgdtq %0" : : "m"(GDTR));
    
    // NOTE(vak): Load code segment offset

    __asm volatile
    (
        "   movq $DummyLabel, %%rax\n"
        "   push $0x08\n"
        "   push %%rax\n"
        "   lretq\n"
        "DummyLabel:\n"
        : : : "rax"
    );

    // NOTE(vak): Load data segment offset

    __asm volatile
    (
        "movw $0x10, %%ax\n"
        "movw %%ax, %%ds\n"
        "movw %%ax, %%es\n"
        "movw %%ax, %%fs\n"
        "movw %%ax, %%gs\n"
        "movw %%ax, %%ss\n"
        : : : "ax"
    );
}

local void KernelEntry(void)
{
    x64Setup();

    for (;;);
}


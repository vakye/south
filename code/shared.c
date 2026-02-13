
local void ZeroMemory(void* DestInit, usize Size)
{
    u8* Dest = (u8*)DestInit;
    while (Size--) *Dest++ = 0;
}

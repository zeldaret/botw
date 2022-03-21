#include <array>

#include <codec/seadHashCRC16.h>

namespace sead
{
u16 HashCRC16::sTable[256];
bool HashCRC16::sInitialized = false;

void HashCRC16::initialize()
{
    for (u32 i = 0; i < std::size(sTable); ++i)
    {
        u32 val = i;
        for (int j = 0; j < 8; ++j)
            val = ((val & 1) == 0) ? (val >> 1) : ((val >> 1) ^ 0xA001);
        sTable[i] = val;
    }
    sInitialized = true;
}

u32 HashCRC16::calcHash(const void* ptr, u32 size)
{
    Context ctx;
    return calcHashWithContext(&ctx, ptr, size);
}

u32 HashCRC16::calcHashWithContext(Context* context, const void* ptr, u32 size)
{
    if (!sInitialized)
        initialize();

    u32 hash = context->hash;
    const u8* data = static_cast<const u8*>(ptr);
    while (size--)
        hash = sTable[*data++ ^ (hash & 0xFF)] ^ (hash >> 8);
    context->hash = hash;
    return hash;
}

u32 HashCRC16::calcStringHash(const char* str)
{
    Context ctx;
    return calcStringHashWithContext(&ctx, str);
}

u32 HashCRC16::calcStringHashWithContext(Context* context, const char* str)
{
    if (!sInitialized)
        initialize();

    u32 hash = context->hash;
    while (*str)
        hash = sTable[*str++ ^ (hash & 0xFF)] ^ (hash >> 8);
    context->hash = hash;
    return hash;
}

}  // namespace sead

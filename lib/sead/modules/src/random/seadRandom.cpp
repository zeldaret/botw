#include "random/seadRandom.h"
#include "time/seadTickTime.h"

namespace sead
{
void Random::init()
{
    TickTime now;
    init(static_cast<u32>(now.toTicks()));
}

void Random::init(u32 seed)
{
    const u32 mt_constant = 0x6C078965;
    mX = mt_constant * (seed ^ (seed >> 30u)) + 1;
    mY = mt_constant * (mX ^ (mX >> 30u)) + 2;
    mZ = mt_constant * (mY ^ (mY >> 30u)) + 3;
    mW = mt_constant * (mZ ^ (mZ >> 30u)) + 4;
}

void Random::init(u32 seed_x, u32 seed_y, u32 seed_z, u32 seed_w)
{
    if ((seed_x | seed_y | seed_z | seed_w) == 0)
    {
        SEAD_ASSERT_MSG(false, "seeds must not be all zero.");
        seed_w = 0x48077044;
        seed_z = 0x714ACB41;
        seed_y = 0x6C078967;
        seed_x = 1;
    }
    mX = seed_x;
    mY = seed_y;
    mZ = seed_z;
    mW = seed_w;
}

u32 Random::getU32()
{
    u32 x = mX ^ (mX << 11u);
    mX = mY;
    mY = mZ;
    mZ = mW;
    mW = mW ^ (mW >> 19u) ^ x ^ (x >> 8u);
    return mW;
}

u64 Random::getU64()
{
    return u64(getU32()) << 32u | getU32();
}

void Random::getContext(u32* x, u32* y, u32* z, u32* w) const
{
    *x = mX;
    *y = mY;
    *z = mZ;
    *w = mW;
}
}  // namespace sead

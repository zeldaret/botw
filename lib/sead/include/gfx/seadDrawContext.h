#pragma once

#include "basis/seadTypes.h"
#include "prim/seadRuntimeTypeInfo.h"

namespace sead
{
class DrawContext
{
    SEAD_RTTI_BASE(DrawContext)
public:
    DrawContext();
    virtual ~DrawContext();

private:
    u32 _8;
    u32 _c;
    u64 _10;
    u8 _18[0xC0 - 0x18];
    u64 _c0;
    u64 _c8;
    u64 _d0;
    u64 _d8;
    u64 _e0;
    u64 _e8;
};

}  // namespace sead

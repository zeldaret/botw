#pragma once

#include "basis/seadTypes.h"

namespace sead
{
class StreamSrc
{
public:
    virtual u32 read(void* data, u32 size) = 0;
    virtual u32 write(const void* data, u32 size) = 0;
    virtual u32 skip(s32 offset) = 0;
    virtual void rewind() = 0;
    virtual bool isEOF() = 0;
    virtual bool flush() { return true; }
};
}  // namespace sead

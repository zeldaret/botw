#pragma once

#include "basis/seadTypes.h"
#include "prim/seadEndian.h"
#include "prim/seadSafeString.h"

namespace sead
{
class StreamSrc;

class StreamFormat
{
public:
    virtual u8 readU8(StreamSrc*, Endian::Types) = 0;
    virtual u16 readU16(StreamSrc*, Endian::Types) = 0;
    virtual u32 readU32(StreamSrc*, Endian::Types) = 0;
    virtual u64 readU64(StreamSrc*, Endian::Types) = 0;
    virtual s8 readS8(StreamSrc*, Endian::Types) = 0;
    virtual s16 readS16(StreamSrc*, Endian::Types) = 0;
    virtual s32 readS32(StreamSrc*, Endian::Types) = 0;
    virtual s64 readS64(StreamSrc*, Endian::Types) = 0;
    virtual f32 readF32(StreamSrc*, Endian::Types) = 0;
    virtual void readBit(StreamSrc*, void*, u32) = 0;
    virtual void readString(StreamSrc*, BufferedSafeString*, u32) = 0;
    virtual u32 readMemBlock(StreamSrc*, void*, u32) = 0;
    virtual void writeU8(StreamSrc*, Endian::Types, u8) = 0;
    virtual void writeU16(StreamSrc*, Endian::Types, u16) = 0;
    virtual void writeU32(StreamSrc*, Endian::Types, u32) = 0;
    virtual void writeU64(StreamSrc*, Endian::Types, u64) = 0;
    virtual void writeS8(StreamSrc*, Endian::Types, s8) = 0;
    virtual void writeS16(StreamSrc*, Endian::Types, s16) = 0;
    virtual void writeS32(StreamSrc*, Endian::Types, s32) = 0;
    virtual void writeS64(StreamSrc*, Endian::Types, s64) = 0;
    virtual void writeF32(StreamSrc*, Endian::Types, f32) = 0;
    virtual void writeBit(StreamSrc*, const void*, u32) = 0;
    virtual void writeString(StreamSrc*, const SafeString&, u32) = 0;
    virtual void writeMemBlock(StreamSrc*, const void*, u32) = 0;
    virtual void writeDecorationText(StreamSrc*, const SafeString&) = 0;
    virtual void writeNullChar(StreamSrc*) = 0;
    virtual void skip(StreamSrc*, u32) = 0;
    virtual void flush(StreamSrc*) = 0;
    virtual void rewind(StreamSrc*) = 0;
};
}  // namespace sead

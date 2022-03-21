#pragma once

#include "basis/seadTypes.h"
#include "prim/seadEndian.h"
#include "prim/seadSafeString.h"

namespace sead
{
class StreamFormat;
class StreamSrc;

class Stream
{
public:
    enum class Modes
    {
        Binary = 0,
        Text = 1,
    };

    Stream();
    Stream(StreamSrc* src, Modes mode);
    Stream(StreamSrc* src, StreamFormat* format);
    virtual ~Stream() = default;

    void skip(u32);
    void skip(u32, u32);
    void rewind();
    bool isEOF();

    void setBinaryEndian(Endian::Types endian);
    void setMode(Modes mode);
    void setUserFormat(StreamFormat* format);

protected:
    StreamFormat* mFormat;
    StreamSrc* mSrc;
    Endian::Types mEndian;
};

class ReadStream : public Stream
{
public:
    u8 readU8();
    void readU8(u8&);
    u16 readU16();
    void readU16(u16&);
    u32 readU32();
    void readU32(u32&);
    u64 readU64();
    void readU64(u64&);
    s8 readS8();
    void readS8(s8&);
    s16 readS16();
    void readS16(s16&);
    s32 readS32();
    void readS32(s32&);
    s64 readS64();
    void readS64(s64&);
    f32 readF32();
    void readF32(f32&);
    void readBit(void*, u32);
    void readString(BufferedSafeString*, u32);
    u32 readMemBlock(void*, u32);

private:
    f32 readF32BitImpl_(u32, u32);
    f64 readF64BitImpl_(u32, u32);
};

class WriteStream : public ReadStream
{
public:
    ~WriteStream() override = default;

    void writeU8(u8);
    void writeU16(u16);
    void writeU32(u32);
    void writeU64(u64);
    void writeS8(s8);
    void writeS16(s16);
    void writeS32(s32);
    void writeS64(s64);
    void writeF32(f32);
    void writeBit(const void*, u32);
    void writeString(const SafeString&, u32);
    void writeMemBlock(const void*, u32);
    void writeComment(const SafeString&);
    void writeLineComment(const SafeString&);
    void writeDecorationText(const SafeString&);
    void writeNullChar();
    void flush();

private:
    void writeF32BitImpl_(f32, u32, u32);
    void writeF64BitImpl_(f64, u32, u32);
};
}  // namespace sead

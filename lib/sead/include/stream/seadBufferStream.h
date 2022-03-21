#pragma once

#include "stream/seadStream.h"
#include "stream/seadStreamSrc.h"

namespace sead
{
class BufferReadStreamSrc : public StreamSrc
{
public:
    BufferReadStreamSrc(StreamSrc* src, void* buffer, u32 buffer_size);
    virtual ~BufferReadStreamSrc();

    u32 read(void* data, u32 size) override;
    u32 write(const void* data, u32 size) override;
    u32 skip(s32 offset) override;
    void rewind() override;
    bool isEOF() override;
    bool flush() override;

private:
    StreamSrc* mSrc;
    u8* mBuffer;
    u32 mBufferSize;
    u32 mCurrentSize;
    u32 mCurrentPos;
};

class BufferReadStream : public ReadStream
{
public:
    BufferReadStream(ReadStream* stream, const void* buffer, u32 buffer_size);
    ~BufferReadStream() override;

private:
    BufferReadStreamSrc mSrc;
};

class BufferWriteStreamSrc : public StreamSrc
{
public:
    BufferWriteStreamSrc(StreamSrc* src, void* buffer, u32 buffer_size);
    virtual ~BufferWriteStreamSrc();

    u32 read(void* data, u32 size) override;
    u32 write(const void* data, u32 size) override;
    u32 skip(s32 offset) override;
    void rewind() override;
    bool isEOF() override { return false; }
    bool flush() override;

private:
    StreamSrc* mSrc;
    u8* mBuffer;
    u32 mBufferSize;
    u32 mCurrentPos;
};

class BufferWriteStream : public ReadStream
{
public:
    BufferWriteStream(ReadStream* stream, void* buffer, u32 buffer_size);
    ~BufferWriteStream() override;

private:
    BufferWriteStreamSrc mSrc;
};

class BufferMultiByteTextWriteStreamSrc : public BufferWriteStreamSrc
{
public:
    BufferMultiByteTextWriteStreamSrc(StreamSrc* src, void* buffer, u32 buffer_size);
    ~BufferMultiByteTextWriteStreamSrc() override = default;
    u32 write(const void* data, u32 size) override;
};

class BufferMultiByteTextWriteStream : public WriteStream
{
public:
    BufferMultiByteTextWriteStream(WriteStream* stream, void* buffer, u32 buffer_size);
    ~BufferMultiByteTextWriteStream() override;

private:
    BufferMultiByteTextWriteStreamSrc mSrc;
};

class BufferMultiByteNullTerminatedTextWriteStreamSrc : public BufferMultiByteTextWriteStreamSrc
{
public:
    ~BufferMultiByteNullTerminatedTextWriteStreamSrc() override = default;
    bool flush() override;
};
}  // namespace sead

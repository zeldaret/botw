#pragma once

#include "basis/seadTypes.h"
#include "prim/seadSafeString.h"
#include "stream/seadBufferStream.h"

namespace sead
{
class PrintFormatter;
class StreamSrc;

// region Print outputs
class PrintOutput
{
public:
    virtual ~PrintOutput() = default;
    virtual void write(const char* string, s32 size) = 0;
    void writeLineBreak();
    PrintFormatter& operator<<(PrintFormatter& formatter);
};

class StringPrintOutput : public PrintOutput
{
public:
    explicit StringPrintOutput(BufferedSafeString* buffer);
    ~StringPrintOutput() override = default;
    void write(const char* string, s32 size) override;

protected:
    BufferedSafeString* mBuffer;
    s32 mPos;
};

class StringCutOffPrintOutput : public PrintOutput
{
public:
    explicit StringCutOffPrintOutput(BufferedSafeString* buffer);
    ~StringCutOffPrintOutput() override = default;
    void write(const char* string, s32 size) override;

protected:
    BufferedSafeString* mBuffer;
    s32 mPos;
};

class StreamPrintOutput : public PrintOutput
{
public:
    explicit StreamPrintOutput(StreamSrc* src);
    ~StreamPrintOutput() override;
    void write(const char* string, s32 size) override;

protected:
    StreamSrc* mSrc;
};

class BufferingPrintOutput : public PrintOutput
{
public:
    BufferingPrintOutput(char* buffer, u32 buffer_size);
    ~BufferingPrintOutput() override;
    void write(const char* string, s32 size) override;

protected:
    BufferMultiByteNullTerminatedTextWriteStreamSrc mSrc;
};
// endregion

// region Print formatters
PrintFormatter& flush(PrintFormatter& formatter);

class PrintFormatter
{
public:
    template <typename T, template <typename> class Class>
    class OutImpl
    {
    public:
        static void out(const Class<T>&, const char*, PrintOutput* output);
    };

    PrintFormatter(const char*, PrintOutput* output);

    void setPrintOutput(PrintOutput* output);

    void flush();
    void flushWithLineBreak();

    PrintFormatter& operator,(s8);
    PrintFormatter& operator,(u8);
    PrintFormatter& operator,(s16);
    PrintFormatter& operator,(u16);
    PrintFormatter& operator,(s32);
    PrintFormatter& operator,(u32);
    PrintFormatter& operator<<(char*);
    PrintFormatter& operator<<(const char*);

    PrintFormatter& operator<<(PrintFormatter& (&fn)(PrintFormatter&)) { return fn(*this); }

    template <typename T>
    PrintFormatter& operator,(const T&);

    template <typename T>
    void out(const T&, const char*, PrintOutput* output);

protected:
    bool proceedToFormatMark_(char*);
    static void outputString_(const char*, PrintOutput*, const char*, s32);
    static void outputPtr_(const char*, PrintOutput*, uintptr_t);

    const char* mFormatStr;
    class PrintOutput* mPrintOutput;
    s32 mPos;
    s32 mFormatStrLength;
    bool mX;
};

inline PrintFormatter& flush(PrintFormatter& formatter)
{
    formatter.flush();
    return formatter;
}

class StringPrintFormatter : public PrintFormatter
{
public:
    explicit StringPrintFormatter(BufferedSafeString* string);
    StringPrintFormatter(BufferedSafeString* string, const char*);

protected:
    StringPrintOutput mOutput;
};

class StringCutOffPrintFormatter : public PrintFormatter
{
public:
    explicit StringCutOffPrintFormatter(BufferedSafeString* string);
    StringCutOffPrintFormatter(BufferedSafeString* string, const char*);

protected:
    StringCutOffPrintOutput mOutput;
};

class StreamPrintFormatter : public PrintFormatter
{
public:
    explicit StreamPrintFormatter(StreamSrc* src);
    StreamPrintFormatter(StreamSrc* src, const char*);
    void flushAndWriteNullChar();

protected:
    StreamPrintOutput mOutput;
};

class BufferingPrintFormatter : public PrintFormatter
{
public:
    BufferingPrintFormatter();
    explicit BufferingPrintFormatter(const char*);

protected:
    BufferingPrintOutput mOutput;
    char mBuffer[128];
};
// endregion
}  // namespace sead

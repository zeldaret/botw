#pragma once

#include "basis/seadTypes.h"
#include "container/seadSafeArray.h"

namespace sead
{
class StackTraceBase
{
public:
    StackTraceBase();
    virtual ~StackTraceBase() = default;

    virtual uintptr_t get(s32 index) const = 0;
    virtual s32 size() const = 0;

    void trace(const void*);

protected:
    virtual void clear_() = 0;
    virtual void push_(uintptr_t addr) = 0;
    virtual bool isFull_() = 0;
};

template <s32 Capacity>
class StackTrace : public StackTraceBase
{
public:
    ~StackTrace() override = default;

    uintptr_t get(s32 index) const override
    {
        if (index >= mSize)
            return 0;
        return mBuffer[index];
    }

    s32 size() const override { return mSize; }

protected:
    void clear_() override { mSize = 0; }

    void push_(uintptr_t addr) override
    {
        mBuffer[mSize] = addr;
        ++mSize;
    }

    bool isFull_() override { return mSize >= mBuffer.size(); }

private:
    SafeArray<uintptr_t, Capacity> mBuffer{};
    s32 mSize{};
};
}  // namespace sead

#pragma once

#include <algorithm>
#include <type_traits>

#include <basis/seadNew.h>
#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadPtrUtil.h>

namespace sead
{
class Heap;

template <typename T>
class RingBuffer
{
public:
    RingBuffer() = default;
    RingBuffer(s32 capacity, T* buffer) { setBuffer(capacity, buffer); }
    template <s32 N>
    explicit RingBuffer(T (&array)[N]) : RingBuffer(N, array)
    {
    }

    class iterator
    {
    public:
        explicit iterator(RingBuffer* buffer, s32 index = 0) : mIndex(index), mBuffer(buffer) {}
        bool operator==(const iterator& rhs) const
        {
            return mIndex == rhs.mIndex && mBuffer == rhs.mBuffer;
        }
        bool operator!=(const iterator& rhs) const { return !operator==(rhs); }
        iterator& operator++()
        {
            ++mIndex;
            return *this;
        }
        T& operator*() const { return buffer()(mIndex); }
        T* operator->() const { return &buffer()(mIndex); }
        s32 getIndex() const { return mIndex; }

    private:
        RingBuffer& buffer() const { return *mBuffer; }

        s32 mIndex;
        RingBuffer* mBuffer;
    };

    class constIterator
    {
    public:
        explicit constIterator(const RingBuffer* buffer, s32 index = 0)
            : mIndex(index), mBuffer(buffer)
        {
        }
        bool operator==(const constIterator& rhs) const
        {
            return mIndex == rhs.mIndex && mBuffer == rhs.mBuffer;
        }
        bool operator!=(const constIterator& rhs) const { return !operator==(rhs); }
        constIterator& operator++()
        {
            ++mIndex;
            return *this;
        }
        const T& operator*() const { return buffer()(mIndex); }
        const T* operator->() const { return &buffer()(mIndex); }
        s32 getIndex() const { return mIndex; }

    private:
        const RingBuffer& buffer() const { return *mBuffer; }

        s32 mIndex;
        const RingBuffer* mBuffer;
    };

    iterator begin() { return iterator(this); }
    constIterator begin() const { return constIterator(this); }
    iterator begin(s32 start_idx) { return iterator(this, wrapIndex(start_idx)); }
    constIterator begin(s32 start_idx) const { return constIterator(this, wrapIndex(start_idx)); }
    iterator end() { return iterator(this, mSize); }
    constIterator end() const { return constIterator(this, mSize); }

    void allocBuffer(s32 capacity, s32 alignment) { void(tryAllocBuffer(capacity, alignment)); }

    void allocBuffer(s32 capacity, Heap* heap, s32 alignment = sizeof(void*))
    {
        static_cast<void>(tryAllocBuffer(capacity, heap, alignment));
    }

    bool tryAllocBuffer(s32 capacity, s32 alignment = sizeof(void*))
    {
        SEAD_ASSERT(mBuffer == nullptr);
        if (capacity > 0)
        {
            T* buffer = new (alignment, std::nothrow) T[capacity];
            if (buffer)
            {
                mBuffer = buffer;
                mHead = mSize = 0;
                mCapacity = capacity;
                SEAD_ASSERT_MSG(PtrUtil::isAlignedPow2(mBuffer, sead::Mathi::abs(alignment)),
                                "don't set alignment for a class with destructor");
                return true;
            }
            return false;
        }
        SEAD_ASSERT_MSG(false, "numMax[%d] must be larger than zero", capacity);
        return false;
    }

    bool tryAllocBuffer(s32 capacity, Heap* heap, s32 alignment = sizeof(void*))
    {
        SEAD_ASSERT(mBuffer == nullptr);
        if (capacity > 0)
        {
            T* buffer = new (heap, alignment, std::nothrow) T[capacity];
            if (buffer)
            {
                mBuffer = buffer;
                mHead = mSize = 0;
                mCapacity = capacity;
                SEAD_ASSERT_MSG(PtrUtil::isAlignedPow2(mBuffer, sead::Mathi::abs(alignment)),
                                "don't set alignment for a class with destructor");
                return true;
            }
            return false;
        }
        SEAD_ASSERT_MSG(false, "numMax[%d] must be larger than zero", capacity);
        return false;
    }

    void allocBufferAssert(s32 size, Heap* heap, s32 alignment = sizeof(void*))
    {
        if (!tryAllocBuffer(size, heap, alignment))
            AllocFailAssert(heap, sizeof(T) * size, alignment);
    }

    void freeBuffer()
    {
        if (mBuffer)
        {
            delete[] mBuffer;
            mBuffer = nullptr;
            mCapacity = 0;
            mHead = 0;
            mSize = 0;
        }
    }

    void setBuffer(s32 capacity, T* bufferptr)
    {
        if (capacity < 1)
        {
            SEAD_ASSERT_MSG(false, "numMax[%d] must be larger than zero", capacity);
            return;
        }
        if (!bufferptr)
        {
            SEAD_ASSERT_MSG(false, "bufferptr is null");
            return;
        }
        mBuffer = bufferptr;
        mHead = mSize = 0;
        mCapacity = capacity;
    }

    bool isBufferReady() const { return mBuffer != nullptr; }

    T& operator[](s32 idx)
    {
        if (u32(mSize) <= u32(idx))
        {
            SEAD_ASSERT_MSG(false, "index exceeded [%d/%d/%d]", idx, mSize, mCapacity);
            return mBuffer[0];
        }
        return *unsafeGet(idx);
    }

    const T& operator[](s32 idx) const
    {
        if (u32(mSize) <= u32(idx))
        {
            SEAD_ASSERT_MSG(false, "index exceeded [%d/%d/%d]", idx, mSize, mCapacity);
            return mBuffer[0];
        }
        return *unsafeGet(idx);
    }

    T* get(s32 idx)
    {
        if (u32(mSize) <= u32(idx))
        {
            SEAD_ASSERT_MSG(false, "index exceeded [%d/%d/%d]", idx, mSize, mCapacity);
            return nullptr;
        }
        return unsafeGet(idx);
    }

    const T* get(s32 idx) const
    {
        if (u32(mSize) <= u32(idx))
        {
            SEAD_ASSERT_MSG(false, "index exceeded [%d/%d/%d]", idx, mSize, mCapacity);
            return nullptr;
        }

        return unsafeGet(idx);
    }

    T& operator()(s32 idx) { return *unsafeGet(idx); }
    const T& operator()(s32 idx) const { return *unsafeGet(idx); }

    T* unsafeGet(s32 idx) { return &mBuffer[calcRealIdx(idx)]; }
    const T* unsafeGet(s32 idx) const { return &mBuffer[calcRealIdx(idx)]; }

    T& front() { return *unsafeGet(0); }
    const T& front() const { return *unsafeGet(0); }

    T& back()
    {
        if (mSize < 1)
        {
            SEAD_ASSERT_MSG(false, "no element");
            return mBuffer[0];
        }
        return *unsafeGet(mSize - 1);
    }

    const T& back() const
    {
        if (mSize < 1)
        {
            SEAD_ASSERT_MSG(false, "no element");
            return mBuffer[0];
        }
        return *unsafeGet(mSize - 1);
    }

    s32 capacity() const { return mCapacity; }
    s32 size() const { return mSize; }

    bool empty() const { return mSize == 0; }
    explicit operator bool() const { return !empty(); }

    T* data() { return mBuffer; }
    const T* data() const { return mBuffer; }

    void forcePushBack(const T& item)
    {
        if (mSize < mCapacity)
        {
            pushBack(item);
            return;
        }

        if (mSize >= 1)
            popFront();
        pushBack(item);
    }

    bool pushBack(const T& item)
    {
        if (mSize >= mCapacity)
            return false;
        *unsafeGet(mSize++) = item;
        return true;
    }

    void forcePushBackwards(const T& item, u32 offset = 1)
    {
        mHead = (mHead < 1 ? mCapacity : mHead) - offset;
        ++mSize;
        *unsafeGet(0) = item;
    }

    bool pushBackwards(const T& item)
    {
        if (mSize >= mCapacity)
            return false;
        forcePushBackwards(item);
        return true;
    }

    T popFront()
    {
        if (mSize >= 1)
        {
            T item = *unsafeGet(0);
            mHead = mHead + 1 < mCapacity ? mHead + 1 : 0;
            --mSize;
            return item;
        }
        SEAD_ASSERT_MSG(false, "no element");
        return {};
    }

    void clear() { mHead = mSize = 0; }

protected:
    s32 calcRealIdx(s32 idx) const
    {
        s32 real_idx = mHead + idx;
        if (real_idx >= mCapacity)
            real_idx -= mCapacity;
        return real_idx;
    }

    s32 wrapIndex(s32 idx) const { return u32(idx) > u32(mSize) ? 0 : idx; }

    T* mBuffer = nullptr;
    s32 mCapacity = 0;
    s32 mHead = 0;
    s32 mSize = 0;
};

template <typename T, s32 N>
class FixedRingBuffer : public RingBuffer<T>
{
public:
    FixedRingBuffer() { RingBuffer<T>::setBuffer(N, mData); }

    void allocBuffer(s32 capacity, s32 alignment) = delete;
    void allocBuffer(s32 capacity, Heap* heap, s32 alignment) = delete;
    bool tryAllocBuffer(s32 capacity, s32 alignment) = delete;
    bool tryAllocBuffer(s32 capacity, Heap* heap, s32 alignment) = delete;
    void allocBufferAssert(s32 size, Heap* heap, s32 alignment) = delete;
    void freeBuffer() = delete;
    void setBuffer(s32 capacity, T* bufferptr) = delete;

private:
    T mData[N];
};
}  // namespace sead

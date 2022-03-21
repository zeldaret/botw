#pragma once

#include <algorithm>
#include "basis/seadNew.h"
#include "basis/seadRawPrint.h"
#include "container/seadFreeList.h"
#include "container/seadPtrArray.h"

namespace sead
{
/// An ObjArray is a container that allocates elements using a FreeList and also keeps an array of
/// pointers for fast access to each element.
template <typename T>
class ObjArray : public PtrArrayImpl
{
public:
    ObjArray() = default;
    ObjArray(s32 max_num, void* buf) { setBuffer(max_num, buf); }

    void allocBuffer(s32 capacity, Heap* heap, s32 alignment = sizeof(void*))
    {
        SEAD_ASSERT(mPtrs == nullptr);

        if (capacity < 1)
        {
            SEAD_ASSERT_MSG(false, "capacity[%d] must be larger than zero", capacity);
            return;
        }

        setBuffer(capacity,
                  new (heap, alignment, std::nothrow) u8[calculateWorkBufferSize(capacity)]);
    }

    bool tryAllocBuffer(s32 capacity, Heap* heap, s32 alignment = sizeof(void*))
    {
        SEAD_ASSERT(mPtrs == nullptr);

        if (capacity < 1)
        {
            SEAD_ASSERT_MSG(false, "capacity[%d] must be larger than zero", capacity);
            return false;
        }

        auto* buf = new (heap, alignment, std::nothrow) u8[calculateWorkBufferSize(capacity)];
        if (!buf)
            return false;

        setBuffer(capacity, buf);
        return true;
    }

    void setBuffer(s32 max_num, void* buf)
    {
        if (!buf)
        {
            SEAD_ASSERT_MSG(false, "buf is null");
            return;
        }

        mFreeList.setWork(buf, ElementSize, max_num);
        PtrArrayImpl::setBuffer(max_num, reinterpret_cast<u8*>(buf) + ElementSize * max_num);
    }

    void freeBuffer()
    {
        if (!isBufferReady())
            return;

        clear();

        if (mFreeList.work())
            delete[] static_cast<u8*>(mFreeList.work());

        mFreeList.reset();
        mPtrs = nullptr;
        mPtrNumMax = 0;
    }

    T* at(s32 pos) const { return static_cast<T*>(PtrArrayImpl::at(pos)); }
    T* unsafeAt(s32 pos) const { return static_cast<T*>(PtrArrayImpl::unsafeAt(pos)); }
    T* operator()(s32 pos) const { return unsafeAt(pos); }
    T* operator[](s32 pos) const { return at(pos); }

    // XXX: Does this use at()?
    T* front() const { return at(0); }
    T* back() const { return at(mPtrNum - 1); }

    void pushBack(const T& item)
    {
        if (isFull())
            SEAD_ASSERT_MSG(false, "buffer full.");
        else
            PtrArrayImpl::pushBack(alloc(item));
    }

    template <class... Args>
    T* emplaceBack(Args&&... args)
    {
        if (isFull())
        {
            SEAD_ASSERT_MSG(false, "buffer full.");
            return nullptr;
        }
        T* item = new (mFreeList.alloc()) T(std::forward<Args>(args)...);
        PtrArrayImpl::pushBack(item);
        return item;
    }

    void insert(s32 pos, const T& item) { PtrArrayImpl::insert(pos, alloc(item)); }

    void erase(int index) { erase(index, 1); }

    void erase(int index, int count)
    {
        if (index + count <= size())
        {
            for (int i = index; i < index + count; ++i)
            {
                auto* ptr = unsafeAt(i);
                ptr->~T();
                mFreeList.free(ptr);
            }
        }
        PtrArrayImpl::erase(index, count);
    }

    void clear()
    {
        for (s32 i = 0; i < mPtrNum; ++i)
        {
            auto* ptr = unsafeAt(i);
            ptr->~T();
            mFreeList.free(ptr);
        }
        mPtrNum = 0;
    }

    using CompareCallback = s32 (*)(const T*, const T*);

    void sort() { sort(compareT); }
    void sort(CompareCallback cmp) { PtrArrayImpl::sort_<T>(cmp); }
    void heapSort() { heapSort(compareT); }
    void heapSort(CompareCallback cmp) { PtrArrayImpl::heapSort_<T>(cmp); }

    bool equal(const ObjArray& other, CompareCallback cmp) const
    {
        return PtrArrayImpl::equal(other, cmp);
    }

    s32 compare(const ObjArray& other, CompareCallback cmp) const
    {
        return PtrArrayImpl::compare(other, cmp);
    }

    s32 binarySearch(const T* ptr) const { return PtrArrayImpl::binarySearch(ptr, compareT); }
    s32 binarySearch(const T* ptr, CompareCallback cmp) const
    {
        return PtrArrayImpl::binarySearch(ptr, cmp);
    }

    bool operator==(const ObjArray& other) const { return equal(other, compareT); }
    bool operator!=(const ObjArray& other) const { return !(*this == other); }
    bool operator<(const ObjArray& other) const { return compare(other) < 0; }
    bool operator<=(const ObjArray& other) const { return compare(other) <= 0; }
    bool operator>(const ObjArray& other) const { return compare(other) > 0; }
    bool operator>=(const ObjArray& other) const { return compare(other) >= 0; }

    void uniq() { PtrArrayImpl::uniq(compareT); }
    void uniq(CompareCallback cmp) { PtrArrayImpl::uniq(cmp); }

    class iterator
    {
    public:
        iterator(T* const* pptr) : mPPtr{pptr} {}
        bool operator==(const iterator& other) const { return mPPtr == other.mPPtr; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
        iterator& operator++()
        {
            ++mPPtr;
            return *this;
        }
        T& operator*() const { return **mPPtr; }
        T* operator->() const { return *mPPtr; }

    private:
        T* const* mPPtr;
    };

    iterator begin() const { return iterator(data()); }
    iterator end() const { return iterator(data() + mPtrNum); }

    class constIterator
    {
    public:
        constIterator(const T* const* pptr) : mPPtr{pptr} {}
        bool operator==(const constIterator& other) const { return mPPtr == other.mPPtr; }
        bool operator!=(const constIterator& other) const { return !(*this == other); }
        constIterator& operator++()
        {
            ++mPPtr;
            return *this;
        }
        const T& operator*() const { return **mPPtr; }
        const T* operator->() const { return *mPPtr; }

    private:
        const T* const* mPPtr;
    };

    constIterator constBegin() const { return constIterator(data()); }
    constIterator constEnd() const { return constIterator(data() + mPtrNum); }

    T** data() const { return reinterpret_cast<T**>(mPtrs); }

private:
    union Node
    {
        void* next_node;
        T elem;
    };

public:
    static constexpr size_t ElementSize = sizeof(Node);

    static constexpr size_t calculateWorkBufferSize(size_t n)
    {
        return n * (ElementSize + sizeof(T*));
    }

protected:
    T* alloc(const T& item)
    {
        void* storage = mFreeList.alloc();
        if (!storage)
            return nullptr;
        return new (storage) T(item);
    }

    static int compareT(const void* a_, const void* b_)
    {
        const T* a = static_cast<const T*>(a_);
        const T* b = static_cast<const T*>(b_);
        if (*a < *b)
            return -1;
        if (*b < *a)
            return 1;
        return 0;
    }

    sead::FreeList mFreeList;
};

template <typename T, s32 N>
class FixedObjArray : public ObjArray<T>
{
public:
    FixedObjArray() : ObjArray<T>(N, &mWork) {}

    // These do not make sense for a *fixed* array.
    void setBuffer(s32 ptrNumMax, void* buf) = delete;
    void allocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*)) = delete;
    bool tryAllocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*)) = delete;
    void freeBuffer() = delete;

private:
    std::aligned_storage_t<ObjArray<T>::calculateWorkBufferSize(N),
                           std::max(alignof(T), alignof(T*))>
        mWork;
};

}  // namespace sead

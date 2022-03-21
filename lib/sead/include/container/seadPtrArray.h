#ifndef SEAD_PTR_ARRAY_H_
#define SEAD_PTR_ARRAY_H_

#include <algorithm>
#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <prim/seadMemUtil.h>
#include <random/seadRandom.h>

namespace sead
{
class Heap;
class Random;

class PtrArrayImpl
{
public:
    PtrArrayImpl() = default;
    PtrArrayImpl(s32 ptrNumMax, void* buf) { setBuffer(ptrNumMax, buf); }

    void setBuffer(s32 ptrNumMax, void* buf);
    void allocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*));
    bool tryAllocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*));
    void freeBuffer();
    bool isBufferReady() const { return mPtrs != nullptr; }

    bool isEmpty() const { return mPtrNum == 0; }
    bool isFull() const { return mPtrNum >= mPtrNumMax; }

    s32 size() const { return mPtrNum; }
    s32 capacity() const { return mPtrNumMax; }

    void erase(s32 position) { erase(position, 1); }
    void erase(s32 position, s32 count);
    void clear() { mPtrNum = 0; }

    // TODO
    void resize(s32 size);
    // TODO
    void unsafeResize(s32 size);

    void swap(s32 pos1, s32 pos2)
    {
        auto* ptr = mPtrs[pos1];
        mPtrs[pos1] = mPtrs[pos2];
        mPtrs[pos2] = ptr;
    }
    void reverse();
    void shuffle()
    {
        Random random;
        shuffle(&random);
    }
    void shuffle(Random* random);

protected:
    using CompareCallbackImpl = int (*)(const void* a, const void* b);

    void* at(s32 idx) const
    {
        if (u32(mPtrNum) <= u32(idx))
        {
            SEAD_ASSERT_MSG(false, "index exceeded [%d/%d]", idx, mPtrNum);
            return nullptr;
        }
        return mPtrs[idx];
    }

    void* unsafeAt(s32 idx) const { return mPtrs[idx]; }

    // XXX: should this use at()?
    void* front() const { return mPtrs[0]; }
    void* back() const { return mPtrs[mPtrNum - 1]; }

    void pushBack(void* ptr)
    {
        if (isFull())
        {
            SEAD_ASSERT_MSG(false, "list is full.");
            return;
        }
        // Simplest insert case, so this is implemented directly without using insert().
        mPtrs[mPtrNum] = ptr;
        ++mPtrNum;
    }

    void pushFront(void* ptr) { insert(0, ptr); }

    void* popBack() { return isEmpty() ? nullptr : mPtrs[--mPtrNum]; }

    void* popFront()
    {
        if (isEmpty())
            return nullptr;

        void* result = mPtrs[0];
        erase(0);
        return result;
    }

    void replace(s32 idx, void* ptr) { mPtrs[idx] = ptr; }

    void* find(const void* ptr, CompareCallbackImpl cmp) const
    {
        for (s32 i = 0; i < mPtrNum; ++i)
        {
            if (cmp(mPtrs[i], ptr) == 0)
                return mPtrs[i];
        }
        return nullptr;
    }

    s32 search(const void* ptr, CompareCallbackImpl cmp) const
    {
        for (s32 i = 0; i < mPtrNum; ++i)
        {
            if (cmp(mPtrs[i], ptr) == 0)
                return i;
        }
        return -1;
    }

    bool equal(const PtrArrayImpl& other, CompareCallbackImpl cmp) const
    {
        if (mPtrNum != other.mPtrNum)
            return false;

        for (s32 i = 0; i < mPtrNum; ++i)
        {
            if (cmp(mPtrs[i], other.mPtrs[i]) != 0)
                return false;
        }
        return true;
    }

    s32 indexOf(const void* ptr) const
    {
        for (s32 i = 0; i < mPtrNum; ++i)
        {
            if (mPtrs[i] == ptr)
                return i;
        }
        return -1;
    }

    void createVacancy(s32 pos, s32 count)
    {
        if (mPtrNum <= pos)
            return;

        MemUtil::copyOverlap(mPtrs + pos + count, mPtrs + pos,
                             s32(sizeof(void*)) * (mPtrNum - pos));
    }

    void insert(s32 idx, void* ptr);
    void insertArray(s32 idx, void* array, s32 array_length, s32 elem_size);
    bool checkInsert(s32 idx, s32 num);

    template <typename T, typename Compare>
    void sort_(Compare cmp)
    {
        // Note: Nintendo did not use <algorithm>
        std::sort(mPtrs, mPtrs + size(), [&](const void* a, const void* b) {
            return cmp(static_cast<const T*>(a), static_cast<const T*>(b)) < 0;
        });
    }

    template <typename T, typename Compare>
    void heapSort_(Compare cmp)
    {
        // Note: Nintendo did not use <algorithm>
        const auto less_cmp = [&](const void* a, const void* b) {
            return cmp(static_cast<const T*>(a), static_cast<const T*>(b)) < 0;
        };
        std::make_heap(mPtrs, mPtrs + size(), less_cmp);
        std::sort_heap(mPtrs, mPtrs + size(), less_cmp);
    }

    void heapSort(CompareCallbackImpl cmp);

    s32 compare(const PtrArrayImpl& other, CompareCallbackImpl cmp) const;
    void uniq(CompareCallbackImpl cmp);

    s32 binarySearch(const void* ptr, CompareCallbackImpl cmp) const
    {
        if (mPtrNum == 0)
            return -1;

        s32 a = 0;
        s32 b = mPtrNum - 1;
        while (a < b)
        {
            const s32 m = (a + b) / 2;
            const s32 c = cmp(mPtrs[m], ptr);
            if (c == 0)
                return m;
            if (c < 0)
                a = m + 1;
            else
                b = m;
        }

        if (cmp(mPtrs[a], ptr) == 0)
            return a;

        return -1;
    }

    s32 mPtrNum = 0;
    s32 mPtrNumMax = 0;
    void** mPtrs = nullptr;
};

template <typename T>
class PtrArray : public PtrArrayImpl
{
public:
    PtrArray() = default;
    PtrArray(s32 ptrNumMax, T** buf) : PtrArrayImpl(ptrNumMax, buf) {}

    T* at(s32 pos) const { return static_cast<T*>(PtrArrayImpl::at(pos)); }
    T* unsafeAt(s32 pos) const { return static_cast<T*>(PtrArrayImpl::unsafeAt(pos)); }
    T* operator()(s32 pos) const { return unsafeAt(pos); }
    T* operator[](s32 pos) const { return at(pos); }

    // XXX: Does this use at()?
    T* front() const { return at(0); }
    T* back() const { return at(mPtrNum - 1); }

    void pushBack(T* ptr) { PtrArrayImpl::pushBack(constCast(ptr)); }
    void pushFront(T* ptr) { PtrArrayImpl::pushFront(constCast(ptr)); }

    T* popBack() { return static_cast<T*>(PtrArrayImpl::popBack()); }
    T* popFront() { return static_cast<T*>(PtrArrayImpl::popFront()); }

    void insert(s32 pos, T* ptr) { PtrArrayImpl::insert(pos, constCast(ptr)); }
    void insert(s32 pos, T* array, s32 count)
    {
        // XXX: is this right?
        PtrArrayImpl::insertArray(pos, constCast(array), count, sizeof(T));
    }
    void replace(s32 pos, T* ptr) { PtrArrayImpl::replace(pos, constCast(ptr)); }

    s32 indexOf(const T* ptr) const { return PtrArrayImpl::indexOf(ptr); }

    using CompareCallback = s32 (*)(const T*, const T*);

    void sort() { sort(compareT); }
    void sort(CompareCallback cmp) { PtrArrayImpl::sort_<T>(cmp); }
    void heapSort() { heapSort(compareT); }
    void heapSort(CompareCallback cmp) { PtrArrayImpl::heapSort_<T>(cmp); }

    bool equal(const PtrArray& other, CompareCallback cmp) const
    {
        return PtrArrayImpl::equal(other, cmp);
    }

    s32 compare(const PtrArray& other, CompareCallback cmp) const
    {
        return PtrArrayImpl::compare(other, cmp);
    }

    T* find(const T* ptr) const
    {
        return PtrArrayImpl::find(ptr,
                                  [](const void* a, const void* b) { return a == b ? 0 : -1; });
    }
    T* find(const T* ptr, CompareCallback cmp) const { return PtrArrayImpl::find(ptr, cmp); }
    s32 search(const T* ptr) const
    {
        return PtrArrayImpl::search(ptr,
                                    [](const void* a, const void* b) { return a == b ? 0 : -1; });
    }
    s32 search(const T* ptr, CompareCallback cmp) const { return PtrArrayImpl::search(ptr, cmp); }
    s32 binarySearch(const T* ptr) const { return PtrArrayImpl::binarySearch(ptr, compareT); }
    s32 binarySearch(const T* ptr, CompareCallback cmp) const
    {
        return PtrArrayImpl::binarySearch(ptr, cmp);
    }

    bool operator==(const PtrArray& other) const { return equal(other, compareT); }
    bool operator!=(const PtrArray& other) const { return !(*this == other); }
    bool operator<(const PtrArray& other) const { return compare(other) < 0; }
    bool operator<=(const PtrArray& other) const { return compare(other) <= 0; }
    bool operator>(const PtrArray& other) const { return compare(other) > 0; }
    bool operator>=(const PtrArray& other) const { return compare(other) >= 0; }

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
    T** dataBegin() const { return data(); }
    T** dataEnd() const { return data() + mPtrNum; }

protected:
    static void* constCast(const T* ptr)
    {
        // Unfortunately, we need to cast away const because several PtrArrayImpl functions
        // only take void* even though the pointed-to object isn't actually modified.
        return static_cast<void*>(const_cast<std::remove_const_t<T>*>(ptr));
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
};

template <typename T, s32 N>
class FixedPtrArray : public PtrArray<T>
{
public:
    FixedPtrArray() : PtrArray<T>(N, mWork) {}

    // These do not make sense for a *fixed* array.
    void setBuffer(s32 ptrNumMax, void* buf) = delete;
    void allocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*)) = delete;
    bool tryAllocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*)) = delete;
    void freeBuffer() = delete;

private:
    // Nintendo uses an untyped u8[N*sizeof(void*)] buffer. That is undefined behavior,
    // so we will not do that.
    T* mWork[N];
};

}  // namespace sead

#endif  // SEAD_PTR_ARRAY_H_

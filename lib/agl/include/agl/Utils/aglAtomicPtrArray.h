#pragma once

#include <basis/seadTypes.h>
#include <prim/seadMemUtil.h>
#include <random/seadRandom.h>
#include <thread/seadAtomic.h>

namespace sead {
class Heap;
}

namespace agl {

namespace detail {

class AtomicPtrArrayImpl {
public:
    AtomicPtrArrayImpl() = default;
    AtomicPtrArrayImpl(s32 ptrNumMax, void* buf) { setBuffer(ptrNumMax, buf); }

    void setBuffer(s32 ptrNumMax, void* buf);
    void allocBuffer(s32 ptrNumMax, sead::Heap* heap, s32 alignment = sizeof(void*));
    void freeBuffer();
    bool isBufferReady() const { return mPtrs != nullptr; }

    bool isEmpty() const { return mPtrNum == 0; }
    bool isFull() const { return mPtrNum == mPtrNumMax; }

    s32 size() const { return mPtrNum; }
    s32 capacity() const { return mPtrNumMax; }

    void erase(s32 position) { erase(position, 1); }
    void erase(s32 position, s32 count);
    void clear() { mPtrNum.exchange(0); }

    void swap(s32 pos1, s32 pos2) {
        auto* ptr = mPtrs[pos1];
        mPtrs[pos1] = mPtrs[pos2];
        mPtrs[pos2] = ptr;
    }
    void shuffle() {
        sead::Random random;
        shuffle(&random);
    }
    void shuffle(sead::Random* random);

protected:
    using CompareCallbackImpl = int (*)(const void* a, const void* b);

    void* at(s32 idx) const {
        if (u32(mPtrNum) <= u32(idx)) {
            SEAD_ASSERT_MSG(false, "index exceeded [%d/%d]", idx, mPtrNum.load());
            return nullptr;
        }
        return mPtrs[idx];
    }

    void* unsafeAt(s32 idx) const { return mPtrs[idx]; }

    // XXX: should this use at()?
    void* front() const { return mPtrs[0]; }
    void* back() const { return mPtrs[mPtrNum - 1]; }

    void pushBack(void* ptr) {
        const s32 idx = mPtrNum++;
        SEAD_ASSERT_MSG(idx < mPtrNumMax, "index = %d, mPtrNumMax = %d", idx, mPtrNumMax.load());
        mPtrs[idx] = ptr;
    }

    void* popBack() { return isEmpty() ? nullptr : mPtrs[--mPtrNum]; }

    void* popFront() {
        if (isEmpty())
            return nullptr;

        void* result = mPtrs[0];
        erase(0);
        return result;
    }

    void* find(const void* ptr, CompareCallbackImpl cmp) const {
        for (s32 i = 0; i < mPtrNum; ++i) {
            if (cmp(ptr, mPtrs[i]) == 0)
                return mPtrs[i];
        }
        return nullptr;
    }

    s32 search(const void* ptr, CompareCallbackImpl cmp) const {
        for (s32 i = 0; i < mPtrNum; ++i) {
            if (cmp(ptr, mPtrs[i]) == 0)
                return i;
        }
        return -1;
    }

    bool equal(const AtomicPtrArrayImpl& other, CompareCallbackImpl cmp) const {
        if (mPtrNum != other.mPtrNum)
            return false;

        for (s32 i = 0; i < mPtrNum; ++i) {
            if (cmp(mPtrs[i], other.mPtrs[i]) != 0)
                return false;
        }
        return true;
    }

    s32 indexOf(const void* ptr) const {
        for (s32 i = 0; i < mPtrNum; ++i) {
            if (mPtrs[i] == ptr)
                return i;
        }
        return -1;
    }

    void sort(CompareCallbackImpl cmp);
    void heapSort(CompareCallbackImpl cmp);

    sead::Atomic<s32> mPtrNum = 0;
    sead::Atomic<s32> mPtrNumMax = 0;
    void** mPtrs = nullptr;
};

}  // namespace detail

namespace utl {

template <typename T>
class AtomicPtrArray : public detail::AtomicPtrArrayImpl {
public:
    AtomicPtrArray() = default;
    AtomicPtrArray(s32 ptrNumMax, T** buf) : AtomicPtrArrayImpl(ptrNumMax, buf) {}

    T* at(s32 pos) const { return static_cast<T*>(AtomicPtrArrayImpl::at(pos)); }
    T* unsafeAt(s32 pos) const { return static_cast<T*>(AtomicPtrArrayImpl::unsafeAt(pos)); }
    T* operator[](s32 pos) const { return at(pos); }

    // XXX: Does this use at()?
    T* front() const { return at(0); }
    T* back() const { return at(mPtrNum - 1); }

    void pushBack(T* ptr) { AtomicPtrArrayImpl::pushBack(ptr); }

    T* popBack() { return static_cast<T*>(AtomicPtrArrayImpl::popBack()); }
    T* popFront() { return static_cast<T*>(AtomicPtrArrayImpl::popFront()); }

    s32 indexOf(const T* ptr) const { return AtomicPtrArrayImpl::indexOf(ptr); }

    using CompareCallback = s32 (*)(const T*, const T*);

    void sort() { AtomicPtrArrayImpl::sort(compareT); }
    void sort(CompareCallback cmp) { AtomicPtrArrayImpl::sort(cmp); }
    void heapSort() { AtomicPtrArrayImpl::heapSort(compareT); }
    void heapSort(CompareCallback cmp) { AtomicPtrArrayImpl::heapSort(cmp); }

    bool equal(const AtomicPtrArray& other, CompareCallback cmp) const {
        return AtomicPtrArrayImpl::equal(other, cmp);
    }

    T* find(const T* ptr) const { return AtomicPtrArrayImpl::find(ptr, compareT); }
    T* find(const T* ptr, CompareCallback cmp) const { return AtomicPtrArrayImpl::find(ptr, cmp); }
    s32 search(const T* ptr) const { return AtomicPtrArrayImpl::search(ptr, compareT); }
    s32 search(const T* ptr, CompareCallback cmp) const {
        return AtomicPtrArrayImpl::search(ptr, cmp);
    }

    bool operator==(const AtomicPtrArray& other) const { return equal(other, compareT); }
    bool operator!=(const AtomicPtrArray& other) const { return !(*this == other); }

    class iterator {
    public:
        iterator(T* const* pptr) : mPPtr{pptr} {}
        bool operator==(const iterator& other) const { return mPPtr == other.mPPtr; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
        iterator& operator++() {
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

    class constIterator {
    public:
        constIterator(const T* const* pptr) : mPPtr{pptr} {}
        bool operator==(const constIterator& other) const { return mPPtr == other.mPPtr; }
        bool operator!=(const constIterator& other) const { return !(*this == other); }
        constIterator& operator++() {
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

protected:
    static int compareT(const T* a, const T* b) {
        if (*a < *b)
            return -1;
        if (*a > *b)
            return 1;
        return 0;
    }
};

template <typename T, s32 N>
class FixedPtrArray : public AtomicPtrArray<T> {
public:
    FixedPtrArray() { AtomicPtrArray<T>::setBuffer(N, mWork); }

    // These do not make sense for a *fixed* array.
    void setBuffer(s32 ptrNumMax, void* buf) = delete;
    void allocBuffer(s32 ptrNumMax, sead::Heap* heap, s32 alignment = sizeof(void*)) = delete;
    bool tryAllocBuffer(s32 ptrNumMax, sead::Heap* heap, s32 alignment = sizeof(void*)) = delete;
    void freeBuffer() = delete;

private:
    // Nintendo uses an untyped u8[N*sizeof(void*)] buffer. That is undefined behavior,
    // so we will not do that.
    T* mWork[N];
};

}  // namespace utl

}  // namespace agl

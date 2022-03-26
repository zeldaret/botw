#pragma once

#include <basis/seadRawPrint.h>
#include <container/seadBuffer.h>
#include <math/seadMathCalcCommon.h>
#include <thread/seadAtomic.h>

namespace ksys::util {

/// A lock-free multiple producer, single consumer queue.
///
/// Values are stored in a ring buffer of T*.
template <typename T>
class LockFreeQueue {
public:
    LockFreeQueue() = default;
    /// @warning This does not automatically free elements.
    ~LockFreeQueue() = default;

    /// Allocate the underlying buffer.
    /// @param capacity Buffer capacity. *Must* be a power of 2.
    void alloc(int capacity, sead::Heap* heap) {
        SEAD_ASSERT(sead::Mathi::isPow2(capacity));
        mBuffer.allocBufferAssert(capacity, heap);
        mBuffer.fill(nullptr);
    }

    void freeBuffer() { mBuffer.freeBuffer(); }

    int getSize() const { return mWriteIdx - mReadIdx; }
    int getCapacity() const { return mBuffer.size(); }

    /// Pop an element from the front of the queue. Non-blocking.
    /// @returns a non-null pointer to an element or nullptr if the queue is empty.
    // NON_MATCHING: control flow is a total mess
    T* pop() {
        while (getSize() > 0) {
            // No need to check if mWriteIdx has changed: the only thing that *could*
            // happen is mWriteIdx being incremented by a producer. In that situation
            // mWriteIdx - read_idx > 0 still holds.

            T* value = get(mReadIdx);
            if (!value) {
                SEAD_ASSERT_MSG(false, "corrupted buffer");
                return nullptr;
            }

            // Advance the read position and return the value if it's not a dummy pointer.
            get(mReadIdx++) = nullptr;
            if (uintptr_t(value) != uintptr_t(-1))
                return value;
        }
        return nullptr;
    }

    /// Push a new element at the back of the queue. Non-blocking: may fail if the queue is full.
    /// @param value The value to insert. Must not be nullptr.
    bool push(T* value) {
        if (!value)
            return false;

        while (true) {
            const u32 write_idx = mWriteIdx;
            if (int(write_idx) - int(mReadIdx) >= getCapacity()) {
                // The buffer is full.
                return false;
            }

            // There is no need to check whether mReadIdx has changed here:
            // the only change that could occur is mReadIdx being incremented by a consumer.
            // If we passed the capacity check, it's okay if the capacity increases.

            if (!mWriteIdx.compareExchange(write_idx, write_idx + 1)) {
                // A producer inserted an element after we checked the capacity. Try again.
                continue;
            }

            get(write_idx) = value;
            return true;
        }
    }

    /// Erase an element from the queue.
    /// @warning Not thread safe!
    void erase(T* value) {
        for (u32 i = mReadIdx; i < mWriteIdx; ++i) {
            if (get(i) == value)
                get(i) = reinterpret_cast<T*>(uintptr_t(-1));
        }
    }

private:
    T*& get(u32 idx) { return mBuffer(moduloCapacity(idx)); }
    const T*& get(u32 idx) const { return mBuffer(moduloCapacity(idx)); }

    int moduloCapacity(u32 idx) const {
        // Because the capacity is a power of 2, we can avoid costly divisions
        // and instead rely on x % 2^n being equal to x & (2^n - 1).
        return idx & (getCapacity() - 1);
    }

    sead::Buffer<T*> mBuffer;
    sead::Atomic<u32> mWriteIdx;
    u32 mReadIdx{};
};

}  // namespace ksys::util

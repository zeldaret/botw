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

        for (int i = 0, n = getCapacity(); i < n; ++i)
            mBuffer(i) = nullptr;
    }

    void freeBuffer() { mBuffer.freeBuffer(); }

    int getCapacity() const { return mBuffer.size(); }

    /// Pop an element from the front of the queue. Non-blocking.
    /// @returns a non-null pointer to an element or nullptr if the queue is empty.
    T* pop() {
        while (true) {
            int read_idx = mReadIdx;
            if (mWriteIdx - read_idx <= 0) {
                // The queue is empty.
                return nullptr;
            }

            // No need to check if mWriteIdx has changed: the only thing that *could*
            // happen is mWriteIdx being incremented by a producer. In that situation
            // mWriteIdx - read_idx > 0 still holds.

            T* value = get(read_idx);
            if (!value) {
                SEAD_ASSERT_MSG(false, "corrupted buffer");
                return nullptr;
            }

            // Advance the read position and return the value if it's not a dummy pointer.
            mReadIdx = read_idx + 1;
            get(read_idx) = nullptr;
            if (uintptr_t(value) != uintptr_t(-1))
                return value;
        }
    }

    /// Push a new element at the back of the queue. Non-blocking: may fail if the queue is full.
    /// @param value The value to insert. Must not be nullptr.
    bool push(T* value) {
        if (!value)
            return false;

        while (true) {
            const int write_idx = mWriteIdx;
            if (write_idx - mReadIdx >= getCapacity()) {
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

private:
    T*& get(int idx) { return mBuffer(moduloCapacity(idx)); }
    const T*& get(int idx) const { return mBuffer(moduloCapacity(idx)); }

    int moduloCapacity(int idx) const {
        // Because the capacity is a power of 2, we can avoid costly divisions
        // and instead rely on x % 2^n being equal to x & (2^n - 1).
        return idx & (getCapacity() - 1);
    }

    sead::Buffer<T*> mBuffer;
    sead::Atomic<int> mWriteIdx;
    int mReadIdx{};
};

}  // namespace ksys::util

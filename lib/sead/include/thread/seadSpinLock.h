#pragma once

#include "basis/seadTypes.h"
#include "thread/seadAtomic.h"

namespace sead
{
class Thread;

class SpinLock
{
public:
    SpinLock();
    ~SpinLock();

    SpinLock(const SpinLock&) = delete;
    SpinLock& operator=(const SpinLock&) = delete;

    void lock();
    bool tryLock();
    void unlock();

    bool try_lock() { return tryLock(); }

private:
    Atomic<Thread*> mOwnerThread;
    u32 mCount = 0;
};
}  // namespace sead

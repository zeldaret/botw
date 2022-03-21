#include "thread/seadReadWriteLock.h"
#include "prim/seadScopedLock.h"
#include "thread/seadThread.h"

namespace sead
{
ReadWriteLock::ReadWriteLock() = default;

ReadWriteLock::~ReadWriteLock() = default;

void ReadWriteLock::readLock()
{
    ScopedLock<SemaphoreLock> lock(&mReadLock);

    if (mNumReaders.increment() == 0)
        mWriteLock.lock();
}

void ReadWriteLock::readUnlock()
{
    if (mNumReaders.decrement() == 1)
        mWriteLock.unlock();
}

void ReadWriteLock::writeLock()
{
    Thread* current_thread = ThreadMgr::instance()->getCurrentThread();
    if (mWriterThread != current_thread)
    {
        if (mNumWriters.increment() == 0)
            mReadLock.lock();

        mWriteLock.lock();
        mWriterThread = current_thread;
    }
    ++mWritingThreadCount;
}

// NON_MATCHING: see SemaphoreLock::unlock
void ReadWriteLock::writeUnlock()
{
    Thread* current_thread = ThreadMgr::instance()->getCurrentThread();
    if (mWriterThread != current_thread)
    {
        SEAD_ASSERT_MSG(false, "This thread[%p] does not have the lock.", current_thread);
        return;
    }

    if (!current_thread || mWritingThreadCount == 0 || int(mWritingThreadCount) < 0)
    {
        SEAD_ASSERT_MSG(
            false,
            "mWritingThreadCount[%d] must not be 0 and current_thread[%p] must not be nullptr",
            mWritingThreadCount, current_thread);
        return;
    }

    --mWritingThreadCount;
    if (mWritingThreadCount == 0)
    {
        mWriterThread = nullptr;
        mWriteLock.unlock();
        if (mNumWriters.decrement() == 1)
            mReadLock.unlock();
    }
}

ReadWriteLock::SemaphoreLock::SemaphoreLock() = default;

void ReadWriteLock::SemaphoreLock::lock()
{
    if (mLockCount.increment())
        mSemaphore.lock();
}

void ReadWriteLock::SemaphoreLock::unlock()
{
    if (mLockCount.decrement() != 1)
        mSemaphore.unlock();
}
}  // namespace sead

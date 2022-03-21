#include "thread/seadSpinLock.h"
#include "thread/seadThread.h"

namespace sead
{
SpinLock::SpinLock() = default;

SpinLock::~SpinLock() = default;

void SpinLock::lock()
{
    Thread* current_thread = ThreadMgr::instance()->getCurrentThread();
    if (mOwnerThread.load() == current_thread)
    {
        ++mCount;
        return;
    }

    while (!mOwnerThread.compareExchange(nullptr, current_thread))
        continue;

    SEAD_ASSERT_MSG(mCount == 0, "mCount[%u] must be 0", mCount);
    mCount = 1;
}

bool SpinLock::tryLock()
{
    Thread* current_thread = ThreadMgr::instance()->getCurrentThread();
    if (mOwnerThread.load() == current_thread)
    {
        ++mCount;
        return true;
    }

    if (!mOwnerThread.compareExchange(nullptr, current_thread))
        return false;

    SEAD_ASSERT_MSG(mCount == 0, "mCount[%u] must be 0", mCount);
    mCount = 1;
    return true;
}

void SpinLock::unlock()
{
    Thread* current_thread = ThreadMgr::instance()->getCurrentThread();
    if (mOwnerThread.load() != current_thread)
    {
        SEAD_ASSERT_MSG(false, "This thread[%p] does not have the lock.", current_thread);
        return;
    }

    SEAD_ASSERT_MSG(mCount != 0 && current_thread != nullptr,
                    "mCount[%u] must not be 0 and my_thread[%p] must not be nullptr", mCount,
                    current_thread);

    --mCount;
    if (mCount == 0)
        mOwnerThread.exchange(nullptr);
}
}  // namespace sead

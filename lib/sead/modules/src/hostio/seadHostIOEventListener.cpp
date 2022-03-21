#include "hostio/seadHostIOEventListener.h"
#include "basis/seadRawPrint.h"
#include "hostio/seadHostIOThreadLock.h"

namespace sead::hostio
{
u32 LifeCheckable::sCurrentCreateID = 1;
LifeCheckable* LifeCheckable::sTopInstance = nullptr;

LifeCheckable* LifeCheckable::searchInstanceFromCreateID(u32 createID)
{
    ThreadLock lock;
    for (auto instance = sTopInstance; instance; instance = instance->mNext)
    {
        if (instance->getCreateID() == createID)
            return instance;
    }
    return nullptr;
}

// NON_MATCHING: regalloc
void LifeCheckable::disposeHostIOImpl_()
{
    ThreadLock lock;
    if (sTopInstance == this)
    {
        SEAD_ASSERT(mPrev == nullptr);
        if (mNext)
        {
            sTopInstance = mNext;
            mNext->mPrev = nullptr;
        }
        else
        {
            sTopInstance = nullptr;
        }
    }
    else
    {
        SEAD_ASSERT(mPrev != nullptr);
        mPrev->mNext = mNext;
        if (mNext)
        {
            SEAD_ASSERT(mNext->mPrev == this);
            mNext->mPrev = mPrev;
        }
    }
}

void LifeCheckable::initialize_()
{
    ThreadLock lock;
    mCreateID = sCurrentCreateID;
    // NON_MATCHING: weird increment code
    sCurrentCreateID += sCurrentCreateID == 0xffffffff ? 2 : 1;

    if (sTopInstance)
    {
        mNext = sTopInstance;
        sTopInstance->mPrev = this;
    }
    sTopInstance = this;
}

LifeCheckable::DisposeHostIOCaller::~DisposeHostIOCaller()
{
    if (!mInstance)
        return;
    mInstance->disposeHostIO();
    mInstance = nullptr;
}
}  // namespace sead::hostio

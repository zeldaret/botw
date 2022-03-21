#include "thread/seadThread.h"
#include "basis/seadRawPrint.h"
#include "prim/seadBitUtil.h"
#include "prim/seadPtrUtil.h"
#include "prim/seadScopedLock.h"
#include "thread/seadThreadUtil.h"

namespace sead
{
const s32 Thread::cDefaultPriority = 0x10;

bool Thread::sendMessage(MessageQueue::Element msg, MessageQueue::BlockType block_type)
{
    if (msg == MessageQueue::cNullElement)
    {
        SEAD_ASSERT_MSG(false, "Can not send cNullElement(==%ld)", MessageQueue::cNullElement);
        return false;
    }

    if (isDone())
    {
        SEAD_ASSERT_MSG(false, "Thread is done. Reject message: %ld", msg);
        return false;
    }

    if (mQuitMsg == msg)
    {
        SEAD_ASSERT_MSG(false, "use quit()");
        return false;
    }

    return mMessageQueue.push(msg, block_type);
}

MessageQueue::Element Thread::recvMessage(MessageQueue::BlockType block_type)
{
    if (mState == State::cQuitting)
        return 0;
    return mMessageQueue.pop(block_type);
}

void Thread::quit(bool is_jam)
{
    if (isDone())
    {
        SEAD_WARN("Thread is done. Can not quit.");
        return;
    }

    if (mState == State::cRunning)
        mState = State::cQuitting;

    if (is_jam)
        mMessageQueue.jam(mQuitMsg, MessageQueue::BlockType::Blocking);
    else
        mMessageQueue.push(mQuitMsg, MessageQueue::BlockType::Blocking);
}

void Thread::quitAndWaitDoneSingleThread(bool is_jam)
{
    quit(is_jam);
    waitDone();
}

constexpr u32 cStackCanaryMagic = 0x5EAD5CEC;

static bool checkStackMagic(uintptr_t addr)
{
    return BitUtil::bitCastPtr<u32>(reinterpret_cast<const void*>(addr)) == cStackCanaryMagic;
}

s32 Thread::calcStackUsedSizePeak() const
{
#ifdef SEAD_DEBUG
    // FIXME
    return 0;
#else
    return 0;
#endif
}

void Thread::checkStackOverFlow(const char* source_file, s32 source_line) const
{
    checkStackPointerOverFlow(source_file, source_line);
    checkStackEndCorruption(source_file, source_line);
}

void Thread::checkStackEndCorruption(const char* source_file, s32 source_line) const
{
    if (ThreadMgr::instance()->getMainThread() == this)
        return;

    const uintptr_t start = getStackCheckStartAddress_();
    if (!start)
        return;

    SEAD_ASSERT_MSG(checkStackMagic(start),
                    "sead::Thread Stack End Corruption! [%s:%p]\n"
                    "  Source File: %s\n"
                    "  Line Number: %d\n"
                    "  Stack Size: %d",
                    getName().cstr(), this,
                    source_file ? source_file : SafeString::cEmptyString.cstr(), source_line,
                    getStackSize());
}

void Thread::checkStackPointerOverFlow(const char* source_file, s32 source_line) const
{
    if (!ThreadMgr::instance() || ThreadMgr::instance()->getCurrentThread() != this)
    {
        SEAD_WARN("sead::Thread::checkStackPointerOverFlow cannot be called from other thread.");
        return;
    }

    const uintptr_t ptr = ThreadUtil::GetCurrentStackPointer();
    const uintptr_t start = getStackCheckStartAddress_();
    if (start)
    {
        SEAD_ASSERT_MSG(start <= ptr,
                        "sead::Thread Stack Pointer Overflow! [%s:%p]\n"
                        "  Source File: %s\n"
                        "  Line Number: %d\n"
                        "  Stack Size: %d, Over Size: %ld",
                        getName().cstr(), this,
                        source_file ? source_file : SafeString::cEmptyString.cstr(), source_line,
                        getStackSize(), start - ptr);
    }
    else
    {
        ThreadMgr::instance()->getCurrentThread();
    }
}

void Thread::setStackOverflowExceptionEnable(bool)
{
    SEAD_WARN("This platform cannot set stack overflow exception.");
}

void Thread::run_()
{
    while (true)
    {
#ifdef SEAD_DEBUG
        checkStackOverFlow(nullptr, 0);
#endif

        const MessageQueue::Element msg = mMessageQueue.pop(mBlockType);
        if (msg == mQuitMsg)
            break;

        calc_(msg);
    }
}

// NON_MATCHING: the first loop gets unrolled and the loop counter is not negated
void Thread::initStackCheck_()
{
    void* const start = reinterpret_cast<void*>(getStackCheckStartAddress_());
    void* const end = PtrUtil::addOffset(mStackTopForCheck, mStackSize);
    u32* addr = static_cast<u32*>(start);

    if (start >= end)
        return;

    const size_t len = uintptr_t(end) + (-uintptr_t(start) - 1);

    for (u32 i = 0; i < ((len / 4 + 1) % 8); ++i)
        *addr++ = cStackCanaryMagic;

    if (len >= 0x1C)
    {
        do
        {
            for (s32 i = 0; i < 8; ++i)
                *addr++ = cStackCanaryMagic;
        } while (addr < end);
    }
}

// NON_MATCHING: see Thread::initStackCheck_
void Thread::initStackCheckWithCurrentStackPointer_()
{
    void* const start = reinterpret_cast<void*>(getStackCheckStartAddress_());
    void* const end = reinterpret_cast<void*>(ThreadUtil::GetCurrentStackPointer());
    u32* addr = static_cast<u32*>(start);

    if (start >= end)
        return;

    const size_t len = uintptr_t(end) + (-uintptr_t(start) - 1);

    for (u32 i = 0; i < ((len / 4 + 1) % 8); ++i)
        *addr++ = cStackCanaryMagic;

    if (len >= 0x1C)
    {
        do
        {
            for (s32 i = 0; i < 8; ++i)
                *addr++ = cStackCanaryMagic;
        } while (addr < end);
    }
}

SEAD_SINGLETON_DISPOSER_IMPL(ThreadMgr)

ThreadMgr::~ThreadMgr()
{
    ScopedLock<CriticalSection> lock(getListCS());

    for (Thread* thread : mList)
        thread->quit(false);

    bool all_done;
    do
    {
        all_done = true;
        for (Thread* thread : mList)
            all_done &= thread->isDone();
        Thread::yield();
    } while (!all_done);

    for (Thread* thread : mList)
        thread->waitDone();

    sInstance = nullptr;
}

void ThreadMgr::initialize(Heap* heap)
{
    initMainThread_(heap);
    SEAD_ASSERT(mMainThread);
}

void ThreadMgr::destroy()
{
    destroyMainThread_();
}

void ThreadMgr::destroyMainThread_()
{
    if (mMainThread)
    {
        delete mMainThread;
        mMainThread = nullptr;
    }
}

bool ThreadMgr::isMainThread() const
{
    return getCurrentThread() == mMainThread;
}

void ThreadMgr::waitDoneMultipleThread(Thread* const* threads, s32 num)
{
    bool all_done;
    do
    {
        all_done = true;
        for (s32 i = 0; i < num; ++i)
            all_done &= threads[i]->isDone();
        Thread::yield();
    } while (!all_done);

    for (s32 i = 0; i < num; ++i)
        threads[i]->waitDone();
}

void ThreadMgr::quitAndWaitDoneMultipleThread(Thread** threads, s32 num, bool is_jam)
{
    for (s32 i = 0; i < num; ++i)
        threads[i]->quit(is_jam);

    waitDoneMultipleThread(threads, num);
}

void ThreadMgr::checkCurrentThreadStackOverFlow(const char* source_file, s32 source_line)
{
    if (!ThreadMgr::instance())
        return;
    if (Thread* thread = ThreadMgr::instance()->getCurrentThread())
        thread->checkStackOverFlow(source_file, source_line);
}

void ThreadMgr::checkCurrentThreadStackEndCorruption(const char* source_file, s32 source_line)
{
    if (!ThreadMgr::instance())
        return;
    if (Thread* thread = ThreadMgr::instance()->getCurrentThread())
        thread->checkStackEndCorruption(source_file, source_line);
}

void ThreadMgr::checkCurrentThreadStackPointerOverFlow(const char* source_file, s32 source_line)
{
    if (!ThreadMgr::instance())
        return;
    if (Thread* thread = ThreadMgr::instance()->getCurrentThread())
        thread->checkStackPointerOverFlow(source_file, source_line);
}
}  // namespace sead

#include "basis/seadNew.h"
#include "basis/seadRawPrint.h"
#include "thread/seadThread.h"

namespace sead
{
Thread::Thread(const SafeString& name, Heap* heap, s32 priority, MessageQueue::BlockType block_type,
               MessageQueue::Element quit_msg, s32 stack_size, s32 message_queue_size)
    : INamable(name), mStackSize(stack_size), mBlockType(block_type), mQuitMsg(quit_msg),
      mPriority(priority)
{
    mListNode.mData = this;
    mMessageQueue.allocate(message_queue_size, heap);
    mStackTop = new (heap, 0x1000) u8[stack_size];
    // FIXME: ThreadType has the wrong size
    mThreadInner = new (heap) nn::os::ThreadType;

    const auto result =
        nn::os::CreateThread(mThreadInner, ninThreadFunc_, this, mStackTop, stack_size, mPriority);

    SEAD_ASSERT_MSG(result.IsSuccess(), "CreateThread failed. 0x%08x (module = %d, desc = %d) %s",
                    result.GetInnerValueForDebug(), result.GetModule(), result.GetDescription(),
                    name.cstr());

    nn::os::SetThreadName(mThreadInner, name.cstr());

    if (ThreadMgr::instance())
        ThreadMgr::instance()->addThread_(this);
    else
        SEAD_ASSERT_MSG(false, "ThreadMgr not initialized");
}

Thread::~Thread()
{
    if (!ThreadMgr::instance())
    {
        SEAD_ASSERT_MSG(false, "ThreadMgr not initialized");
        return;
    }

    if (ThreadMgr::instance()->getMainThread() != this)
    {
        ThreadMgr::instance()->removeThread_(this);

        if (mState != State::cQuitting && mState != State::cTerminated)
        {
            if (mState == State::cRunning)
            {
                SEAD_ASSERT_MSG(false, "Thread is running. Do quit and waitDone");
                quitAndWaitDoneSingleThread(false);
            }
        }
        else
        {
            SEAD_ASSERT_MSG(false, "Thread is not done. Do waitDone");
            waitDone();
        }

        nn::os::DestroyThread(mThreadInner);

        if (mThreadInner)
            delete mThreadInner;

        if (mStackTop)
            delete[] static_cast<u8*>(mStackTop);
    }

    mMessageQueue.free();
}

bool Thread::start()
{
    if (mState)
    {
        SEAD_WARN("Thread is running or done. Can not start.\n");
        return false;
    }

    nn::os::StartThread(mThreadInner);

    const u32 id = nn::os::GetThreadId(mThreadInner);
    const int state = mState;
    mId = id;

    if (state == State::cInitialized)
        mState = State::cRunning;

    return true;
}

void Thread::waitDone()
{
    if ((mState.value() | State::cReleased) == State::cReleased)
        return;

    nn::os::WaitThread(mThreadInner);
    SEAD_ASSERT_MSG(mState == State::cTerminated, "Join failed?");
    mState = State::cReleased;
}

void Thread::setPriority(s32 prio)
{
    mPriority = prio;
    if (isActive())
        nn::os::ChangeThreadPriority(mThreadInner, prio);
}

s32 Thread::getPriority() const
{
    return mPriority;
}

void Thread::setAffinity(const CoreIdMask& affinity)
{
    mAffinity = affinity;
    u64 mask = mAffinity;
    const auto available_mask = nn::os::GetThreadAvailableCoreMask();
    SEAD_ASSERT_MSG((~u32(available_mask) & mask) == 0, "invalid core mask. ( mask = %ld )", mask);
    nn::os::SetThreadCoreMask(mThreadInner, -1, mask);
}

void Thread::yield()
{
    nn::os::YieldThread();
}

void Thread::sleep(TickSpan howLong)
{
    nn::os::SleepThread(nn::os::ConvertToTimeSpan(howLong.toTicks()));
}

uintptr_t Thread::getStackCheckStartAddress_() const
{
    return uintptr_t(mStackTopForCheck);
}

void Thread::ninThreadFunc_(void* arg)
{
    auto self = static_cast<Thread*>(arg);

    ThreadMgr::instance()->mThreadPtrTLS.setValue(uintptr_t(self));

    if (self->mAffinity.countOnBits() <= 1)
        nn::os::SetTlsValue(CoreInfo::getCoreNumberTlsSlot(),
                            int(nn::os::GetCurrentCoreNumber()) + 1);

#ifdef SEAD_DEBUG
    uintptr_t stack_addr;
    nn::os::GetCurrentStackInfo(&stack_addr, nullptr);
    self->mStackTopForCheck = reinterpret_cast<void*>(stack_addr);
    self->initStackCheckWithCurrentStackPointer_();
#endif

    const u32 id = nn::os::GetThreadId(self->mThreadInner);
    self->mState = State::cRunning;
    self->mId = id;
    self->run_();
    self->mState = State::cTerminated;
}

Thread::Thread(Heap* heap, nn::os::ThreadType* nn_thread, u32 thread_id)
    : INamable("sead::MainThread"), mStackSize(nn_thread->thread_stack_size),
      mBlockType(MessageQueue::BlockType::NonBlocking), mQuitMsg(0x7FFFFFFF), mId(thread_id),
      mState(State::cRunning), mThreadInner(nn_thread),
      mPriority(nn::os::GetThreadPriority(nn_thread))
{
    mListNode.mData = this;
    mMessageQueue.allocate(32, heap);

    uintptr_t stack_addr;
    size_t stack_size;
    nn::os::GetCurrentStackInfo(&stack_addr, &stack_size);
    mStackTopForCheck = reinterpret_cast<void*>(stack_addr);
    mStackSize = s32(stack_size);

#ifdef SEAD_DEBUG
    initStackCheckWithCurrentStackPointer_();
#endif

    setAffinity(mAffinity);
}

ThreadMgr::ThreadMgr() = default;

u32 ThreadMgr::getCurrentThreadID_()
{
    return u32(uintptr_t(nn::os::GetCurrentThread()));
}

void ThreadMgr::initMainThread_(Heap* heap)
{
    nn::os::ThreadType* nn_thread = nn::os::GetCurrentThread();
    nn::os::ChangeThreadPriority(nn::os::GetCurrentThread(), 16);
    const u64 nn_thread_id = nn::os::GetThreadId(nn_thread);

    auto thread = new (heap) MainThread(heap, nn_thread, nn_thread_id);
    mMainThread = thread;
    mThreadPtrTLS.setValue(uintptr_t(thread));

    nn::os::SetTlsValue(CoreInfo::getCoreNumberTlsSlot(), int(nn::os::GetCurrentCoreNumber()) + 1);
}
}  // namespace sead

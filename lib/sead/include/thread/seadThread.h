#pragma once

#ifdef NNSDK
#include <nn/os.h>
#endif

#include <basis/seadRawPrint.h>
#include <container/seadTList.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeapMgr.h>
#include <hostio/seadHostIONode.h>
#include <hostio/seadHostIOReflexible.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadEnum.h>
#include <prim/seadNamable.h>
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>
#include <thread/seadMessageQueue.h>
#include <thread/seadThreadLocalStorage.h>
#include <time/seadTickSpan.h>

namespace sead
{
class Heap;
class Thread;

using ThreadList = TList<Thread*>;
using ThreadListNode = TListNode<Thread*>;

class Thread : public IDisposer, public INamable, public hostio::Reflexible
{
public:
    SEAD_ENUM(State, cInitialized, cRunning, cQuitting, cTerminated, cReleased);

    Thread(const SafeString& name, Heap* heap, s32 priority, MessageQueue::BlockType block_type,
           MessageQueue::Element quit_msg, s32 stack_size, s32 message_queue_size);
    ~Thread() override;

    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    virtual void destroy() { waitDone(); }

    virtual bool sendMessage(MessageQueue::Element msg, MessageQueue::BlockType block_type);
    virtual MessageQueue::Element recvMessage(MessageQueue::BlockType block_type);
    virtual const MessageQueue& getMessageQueue() const { return mMessageQueue; }

    virtual bool start();
    virtual void quit(bool is_jam);
    virtual void waitDone();
    virtual void quitAndDestroySingleThread(bool is_jam) { quitAndWaitDoneSingleThread(is_jam); }
    virtual void quitAndWaitDoneSingleThread(bool is_jam);

    virtual void setPriority(s32 prio);
    virtual s32 getPriority() const;
    virtual MessageQueue::BlockType getBlockType() const { return mBlockType; }
    virtual s32 getStackSize() const { return mStackSize; }
    virtual s32 calcStackUsedSizePeak() const;

    u32 getId() const { return mId; }
    State getState() const { return mState; }
    bool isDone() const { return mState == State::cTerminated || mState == State::cReleased; }
    bool isActive() const { return mState == State::cRunning || mState == State::cQuitting; }

    const CoreIdMask& getAffinity() const { return mAffinity; }
    void setAffinity(const CoreIdMask& affinity);

    static void yield();
    static void sleep(TickSpan howLong);

    void checkStackOverFlow(const char* source_file, s32 source_line) const;
    void checkStackEndCorruption(const char* source_file, s32 source_line) const;
    void checkStackPointerOverFlow(const char* source_file, s32 source_line) const;
    void setStackOverflowExceptionEnable(bool);

    ThreadListNode* getThreadListNode() { return &mListNode; }

#ifdef SEAD_DEBUG
    void listenPropertyEvent(const hostio::PropertyEvent* event) override;
    void genMessage(hostio::Context* context) override;
#endif

    bool isDefaultPriority() const { return getPriority() == cDefaultPriority; }

    static const s32 cDefaultPriority;

protected:
#ifdef NNSDK
    Thread(Heap* heap, nn::os::ThreadType*, u32);
#endif

    virtual void run_();
    virtual void calc_(MessageQueue::Element msg) = 0;
    virtual uintptr_t getStackCheckStartAddress_() const;

    void initStackCheck_();
    void initStackCheckWithCurrentStackPointer_();

#ifdef NNSDK
    static void ninThreadFunc_(void*);
#endif

    MessageQueue mMessageQueue;
    s32 mStackSize = 0;
    ThreadListNode mListNode;
    Heap* mCurrentHeap = nullptr;
    FindContainHeapCache mFindContainHeapCache;
    MessageQueue::BlockType mBlockType = MessageQueue::BlockType::Blocking;
    MessageQueue::Element mQuitMsg = 0;
    u32 mId = 0;
    State mState = State::cInitialized;
    CoreIdMask mAffinity{CoreId::cMain};
#ifdef NNSDK
    nn::os::ThreadType* mThreadInner = nullptr;
#endif
    void* mStackTop = nullptr;
    void* mStackTopForCheck = nullptr;
    s32 mPriority = 0;
};

class ThreadMgr : public hostio::Node
{
    SEAD_SINGLETON_DISPOSER(ThreadMgr)
public:
    ThreadMgr();
    virtual ~ThreadMgr();

    void initialize(Heap* heap);
    void destroy();

    bool isMainThread() const;
    Thread* getMainThread() const { return mMainThread; }
    Thread* getCurrentThread() const { return reinterpret_cast<Thread*>(mThreadPtrTLS.getValue()); }

    static void waitDoneMultipleThread(Thread* const* threads, s32 num);
    static void quitAndWaitDoneMultipleThread(Thread** threads, s32 num, bool is_jam);

    static void checkCurrentThreadStackOverFlow(const char* source_file, s32 source_line);
    static void checkCurrentThreadStackEndCorruption(const char* source_file, s32 source_line);
    static void checkCurrentThreadStackPointerOverFlow(const char* source_file, s32 source_line);

    CriticalSection* getListCS() { return &mListCS; }

#ifdef SEAD_DEBUG
    void initHostIO();
    void genMessage(hostio::Context* context) override;
    void listenPropertyEvent(const hostio::PropertyEvent* event) override;
#endif

protected:
    friend class Thread;

    void addThread_(Thread* thread)
    {
        ScopedLock<CriticalSection> lock(getListCS());
        mList.pushBack(thread->getThreadListNode());
    }

    void removeThread_(Thread* thread)
    {
        ScopedLock<CriticalSection> lock(getListCS());
        mList.erase(thread->getThreadListNode());
    }

    void initMainThread_(Heap* heap);
    void destroyMainThread_();
    static u32 getCurrentThreadID_();

private:
    ThreadList mList;
    CriticalSection mListCS;
    Thread* mMainThread = nullptr;
    ThreadLocalStorage mThreadPtrTLS;
};

class MainThread : public Thread
{
public:
#ifdef NNSDK
    MainThread(Heap* heap, nn::os::ThreadType* nn_thread, u32 thread_id)
        : Thread(heap, nn_thread, thread_id)
    {
    }
#endif
    ~MainThread() override { mState = State::cTerminated; }

    void destroy() override { SEAD_ASSERT_MSG(false, "Main thread can not destroy"); }
    void quit(bool) override { SEAD_ASSERT_MSG(false, "Main thread can not quit"); }
    void waitDone() override { SEAD_ASSERT_MSG(false, "Main thread can not waitDone"); }
    void quitAndDestroySingleThread(bool) override
    {
        SEAD_ASSERT_MSG(false, "Main thread can not quit");
    }
    void setPriority(s32) override { SEAD_ASSERT_MSG(false, "Main thread can not set priority"); }

protected:
    void calc_(MessageQueue::Element) override {}
};
}  // namespace sead

#include "thread/seadDelegateThread.h"
#include "prim/seadDelegate.h"

namespace sead
{
DelegateThread::DelegateThread(const SafeString& name,
                               IDelegate2<Thread*, MessageQueue::Element>* delegate, Heap* heap,
                               s32 priority, MessageQueue::BlockType block_type,
                               MessageQueue::Element quit_msg, s32 stack_size,
                               s32 message_queue_size)
    : Thread(name, heap, priority, block_type, quit_msg, stack_size, message_queue_size),
      mDelegate(delegate)
{
}

DelegateThread::~DelegateThread() = default;

void DelegateThread::calc_(MessageQueue::Element msg)
{
    mDelegate->invoke(this, msg);
}
}  // namespace sead

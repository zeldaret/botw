#pragma once

#include <thread/seadMessageQueue.h>
#include <thread/seadThread.h>

namespace sead
{
template <typename A1, typename A2>
class IDelegate2;

class DelegateThread : public Thread
{
public:
    DelegateThread(const SafeString& name, IDelegate2<Thread*, MessageQueue::Element>* delegate,
                   Heap* heap, s32 priority, MessageQueue::BlockType block_type,
                   MessageQueue::Element quit_msg, s32 stack_size, s32 message_queue_size);
    ~DelegateThread() override;

protected:
    void calc_(MessageQueue::Element msg) override;

    IDelegate2<Thread*, MessageQueue::Element>* mDelegate;
};

}  // namespace sead

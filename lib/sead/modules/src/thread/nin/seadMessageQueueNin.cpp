#include "basis/seadNew.h"
#include "basis/seadRawPrint.h"
#include "thread/seadMessageQueue.h"

namespace sead
{
MessageQueue::MessageQueue() = default;

MessageQueue::~MessageQueue() = default;

void MessageQueue::allocate(s32 size, Heap* heap)
{
    if (size <= 0)
    {
        SEAD_ASSERT_MSG(false, "MessageQueue size must not be zero");
        return;
    }

    mBuffer = new (heap) Element[size];
    nn::os::InitializeMessageQueue(&mMessageQueueInner, reinterpret_cast<u64*>(mBuffer), size);
}

void MessageQueue::free()
{
    nn::os::FinalizeMessageQueue(&mMessageQueueInner);
    if (mBuffer)
    {
        delete[] mBuffer;
        mBuffer = nullptr;
    }
}

bool MessageQueue::push(MessageQueue::Element message, MessageQueue::BlockType block_type)
{
    if (block_type == BlockType::Blocking)
    {
        nn::os::SendMessageQueue(&mMessageQueueInner, message);
        return true;
    }

    return nn::os::TrySendMessageQueue(&mMessageQueueInner, message);
}

MessageQueue::Element MessageQueue::pop(MessageQueue::BlockType block_type)
{
    u64 message;

    if (block_type == BlockType::Blocking)
    {
        nn::os::ReceiveMessageQueue(&message, &mMessageQueueInner);
        return message;
    }

    if (nn::os::TryReceiveMessageQueue(&message, &mMessageQueueInner))
        return message;
    return 0;
}

MessageQueue::Element MessageQueue::peek(MessageQueue::BlockType block_type) const
{
    u64 message;

    if (block_type == BlockType::Blocking)
    {
        nn::os::PeekMessageQueue(&message, &mMessageQueueInner);
        return message;
    }

    if (nn::os::TryPeekMessageQueue(&message, &mMessageQueueInner))
        return message;
    return 0;
}

bool MessageQueue::jam(MessageQueue::Element message, MessageQueue::BlockType block_type)
{
    if (block_type == BlockType::Blocking)
    {
        nn::os::JamMessageQueue(&mMessageQueueInner, message);
        return true;
    }

    return nn::os::TryJamMessageQueue(&mMessageQueueInner, message);
}
}  // namespace sead

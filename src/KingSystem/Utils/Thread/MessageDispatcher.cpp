#include "KingSystem/Utils/Thread/MessageDispatcher.h"
#include <heap/seadHeapMgr.h>
#include <prim/seadMemUtil.h>
#include <prim/seadScopedLock.h>
#include <thread/seadThread.h>
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "KingSystem/Utils/Thread/MessageReceiverEx.h"

namespace ksys {

MessageQueue::MessageQueue() = default;

MessageQueue::~MessageQueue() {
    MessageQueue::clear();
}

Message* MessageQueue::findUnusedEntry() const {
    for (Message& entry : mMessages) {
        if (!entry.isValid())
            return &entry;
    }
    return nullptr;
}

bool MessageQueue::addMessage(const Message& message) {
    if (!message.getSource().isRegistered())
        return false;

    if (!message.getDestination().isRegistered())
        return false;

    auto* entry = findUnusedEntry();
    if (!entry)
        return false;

    *entry = message;
    return true;
}

void MessageQueue::processQueue(MessageProcessor& processor) {
    for (auto& message : mMessages) {
        if (!message.isValid())
            break;

        if (processor.process(&message))
            message.resetIfValid();
    }
}

void MessageQueue::clear() {
    for (auto it = mMessages.begin(); it != mMessages.end(); ++it)
        it->resetIfValid();
}

MessageDispatcher::DoubleBufferedQueue::DoubleBufferedQueue() = default;

MessageDispatcher::DoubleBufferedQueue::~DoubleBufferedQueue() = default;

bool MessageDispatcher::DoubleBufferedQueue::addMessage(const Message& message) {
    return mBuffer[mActiveIdx ^ 1].addMessage(message);
}

void MessageDispatcher::DoubleBufferedQueue::clear() {
    mBuffer[0].clear();
    mBuffer[1].clear();
}

void MessageDispatcher::DoubleBufferedQueue::processQueue(MessageProcessor& processor) {
    mBuffer[mActiveIdx].processQueue(processor);
}

MessageDispatcher::Queues::DummyLogger::~DummyLogger() = default;

MessageDispatcher::Logger::~Logger() = default;

void MessageDispatcher::Logger::log(const Message& message, bool success) {}

MessageDispatcher::MainQueue::MainQueue() = default;

MessageDispatcher::MainQueue::~MainQueue() = default;

bool MessageDispatcher::MainQueue::addMessage(const Message& message) {
    const bool ret = mQueue.addMessage(message);
    if (ret)
        mHasMessageToProcess = true;
    return ret;
}

void MessageDispatcher::MainQueue::clear() {
    mQueue.clear();
}

void MessageDispatcher::MainQueue::processQueue(MessageProcessor& processor) {
    for (u32 i = 0; mHasMessageToProcess && i < 1000; ++i) {
        mHasMessageToProcess = false;
        mQueue.swapBuffer();
        mQueue.processQueue(processor);
    }
}

MessageDispatcher::Queues::TransceiverIdBuffer::TransceiverIdBuffer() {
    for (auto it = mBuffer.begin(); it != mBuffer.end(); ++it)
        *it = nullptr;
}

MessageDispatcher::Queues::TransceiverIdBuffer::~TransceiverIdBuffer() {
    for (auto it = mBuffer.begin(); it != mBuffer.end(); ++it) {
        if (auto* id = *it; id && id->isRegistered())
            id->reset();
    }
}

MessageDispatcher::Queues::Queues(MessageProcessor::Logger* logger)
    : mProcessor(logger == nullptr ? &mDummyLogger : logger) {}

MessageDispatcher::Queues::~Queues() {
    mQueue.clear();
    mMainQueue.clear();
}

SEAD_SINGLETON_DISPOSER_IMPL(MessageDispatcher)

MessageDispatcher::~MessageDispatcher() {
    mBools.freeBuffer();
    mBoolBuffer.freeBuffer();
    util::safeDelete(mQueues);
}

void MessageDispatcher::init(const InitArg& arg, sead::Heap* heap) {
    heap = util::getHeapOrCurrentHeap(heap);
    sead::ScopedCurrentHeapSetter heap_setter{heap};

    if (arg.set_instance)
        setAsGlobalInstance();

    mQueues = new (heap) Queues(&mLogger);

    mUpdateEndEvent.initialize(true);
    mUpdateEndEvent.setSignal();

    mBoolBuffer.allocBufferAssert(arg.num_bools, heap);
    sead::MemUtil::fillZero(mBoolBuffer.getBufferPtr(), mBoolBuffer.getByteSize());

    mBools.allocBuffer(arg.num_bools, heap);
    for (int i = 0, n = mBoolBuffer.size(); i < n; ++i) {
        mBools.emplaceBack(&mBoolBuffer[i]);
    }

    mFlags.set(Flag::Initialized);
}

bool MessageDispatcher::isProcessingOnCurrentThread() const {
    return mProcessingThread == sead::ThreadMgr::instance()->getCurrentThread();
}

void MessageDispatcher::registerTransceiver(MessageReceiverEx& receiver) {
    const auto lock = sead::makeScopedLock(mCritSection);
    Queues& queues = *mQueues;
    receiver.setQueueId(queues.getId());
    MesTransceiverId** ref = nullptr;
    {
        const auto queue_lock = sead::makeScopedLock(queues.getCritSection());
        MesTransceiverId* id = receiver.getId();

        if (!id->isRegistered()) {
            const auto& pointers = queues.getIdPointers();
            for (auto it = pointers.begin(); it != pointers.end(); ++it) {
                if (*it == nullptr) {
                    ref = it;
                    break;
                }
            }
        }

        if (ref) {
            *ref = id;
            id->self_ref = ref;
        }
    }

    if (!ref) {
        sead::FormatFixedSafeString<128> msg{"↓↓↓\nエントリー数 : %d\n↑↑↑\n", mNumEntries.load()};
        util::PrintDebug(msg);
        return;
    }

    mNumEntries.increment();
    if (!mBools.isEmpty())
        receiver.setFlagPointer(mBools.popFront());
}

void MessageDispatcher::deregisterTransceiver(MessageReceiverEx& receiver) {
    if (receiver.checkFlag() && receiver.isWaitingForAck())
        mUpdateEndEvent.wait();

    const auto lock = sead::makeScopedLock(mCritSection);
    if (!receiver.getId()->isRegistered())
        return;

    auto* ptr = receiver.getFlagPointer();
    if (!ptr)
        return;

    mBools.emplaceBack(ptr);
    receiver.clearFlagPointer();

    {
        const auto queue_lock = sead::makeScopedLock(mQueues->getCritSection());
        auto& id = *receiver.getId();
        if (id.isRegistered()) {
            auto* self = id.self_ref;
            id.self_ref = nullptr;
            *self = nullptr;
        }
    }

    mNumEntries.decrement();
}

bool MessageDispatcher::sendMessage(const MesTransceiverId& src, const MesTransceiverId& dest,
                                    const MessageType& type, void* user_data, bool ack, bool) {
    auto* queues = mQueues;
    const auto message = Message{src, dest, type, user_data, {}, ack};
    const auto lock = sead::makeScopedLock(queues->getCritSection());
    return queues->getQueue().addMessage(message);
}

bool MessageDispatcher::Queues::sendMessageOnProcessingThread(const MesTransceiverId& src,
                                                              const MesTransceiverId& dest,
                                                              const MessageType& type,
                                                              void* user_data, bool ack) {
    const auto message = Message{src, dest, type, user_data, {}, ack};
    if (!isProcessing())
        return false;
    return mMainQueue.addMessage(message);
}

// NON_MATCHING: branching: deduplicated Message destructor call
bool MessageDispatcher::sendMessageOnProcessingThread(const MesTransceiverId& src,
                                                      const MesTransceiverId& dest,
                                                      const MessageType& type, void* user_data,
                                                      bool ack, bool) {
    if (!isProcessingOnCurrentThread())
        return false;
    return mQueues->sendMessageOnProcessingThread(src, dest, type, user_data, ack);
}

struct AddMessageContext : IMessageBrokerRegister::IForEachContext {
    AddMessageContext(MessageQueue* queue, Message* message) : queue(queue), message(message) {}

    void process(const MesTransceiverId& id) override {
        if (!id.isRegistered())
            return;
        message->setDestination(id);
        result = queue->addMessage(*message);
    }

    MessageQueue* queue;
    Message* message;
    bool result = false;
};

bool MessageDispatcher::sendMessage(const MesTransceiverId& src, IMessageBrokerRegister& reg,
                                    const MessageType& type, void* user_data, bool ack, bool) {
    auto queues = mQueues;
    Message::DelayParams delay_params;
    // This should probably be a Queues member function, but putting this here removes
    // the need to include Message.h in the header.
    return [&] {
        auto message = Message{src, type, user_data, delay_params, ack};
        message.setBrokerId_(reg.getId());

        queues->getCritSection().lock();
        AddMessageContext ctx{queues->getQueue().getQueue(), &message};
        reg.forEachRegistered(ctx);
        queues->getCritSection().unlock();
        return ctx.result;
    }();
}

struct AddMessageMainContext : IMessageBrokerRegister::IForEachContext {
    AddMessageMainContext(MessageDispatcher::MainQueue* queue, Message* message)
        : queue(queue), message(message) {}

    void process(const MesTransceiverId& id) override {
        if (!id.isRegistered())
            return;
        message->setDestination(id);
        result = queue->addMessage(*message);
    }

    MessageDispatcher::MainQueue* queue;
    Message* message;
    bool result = false;
};

bool MessageDispatcher::sendMessageOnProcessingThread(const MesTransceiverId& src,
                                                      IMessageBrokerRegister& reg,
                                                      const MessageType& type, void* user_data,
                                                      bool ack, bool) {
    if (!isProcessingOnCurrentThread())
        return false;

    auto queues = mQueues;
    Message::DelayParams delay_params;
    return [&] {
        if (!queues->isProcessing())
            return false;

        auto message = Message{src, type, user_data, delay_params, ack};
        message.setBrokerId_(reg.getId());

        AddMessageMainContext ctx{&queues->getMainQueue(), &message};
        reg.forEachRegistered(ctx);
        return ctx.result;
    }();
}

void MessageDispatcher::Queues::process() {
    {
        const auto lock = sead::makeScopedLock(mCritSection);
        mQueue.swapBuffer();
    }
    mIsProcessing = true;
    mQueue.processQueue(mProcessor);
    mMainQueue.processQueue(mProcessor);
    mIsProcessing = false;
}

// NON_MATCHING: regalloc
void MessageDispatcher::update() {
    mUpdateEndEvent.resetSignal();
    mProcessingThread = sead::ThreadMgr::instance()->getCurrentThread();

    mQueues->process();

    sead::MemUtil::fillZero(mBoolBuffer.getBufferPtr(), mBoolBuffer.getByteSize());
    mProcessingThread = nullptr;
    mUpdateEndEvent.setSignal();
}

}  // namespace ksys

#include "KingSystem/Utils/Thread/MessageDispatcher.h"
#include <heap/seadHeapMgr.h>
#include <prim/seadMemUtil.h>
#include <thread/seadThread.h>
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace ksys {

MessageDispatcher::Queue::Queue() = default;

MessageDispatcher::Queue::~Queue() {
    Queue::clear();
}

Message* MessageDispatcher::Queue::findUnusedEntry() const {
    for (Message& entry : mMessages) {
        if (!entry.isValid())
            return &entry;
    }
    return nullptr;
}

bool MessageDispatcher::Queue::addMessage(const Message& message) {
    if (!Message::checkTransceiver(message.getSource()))
        return false;

    if (!Message::checkTransceiver(message.getDestination()))
        return false;

    auto* entry = findUnusedEntry();
    if (!entry)
        return false;

    *entry = message;
    return true;
}

void MessageDispatcher::Queue::processQueue(MessageProcessor& processor) {
    for (auto& message : mMessages) {
        if (!message.isValid())
            break;

        if (processor.process(&message))
            message.resetIfValid();
    }
}

void MessageDispatcher::Queue::clear() {
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
    mActiveIdx ^= 1;
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
        mQueue.processQueue(processor);
    }
}

MessageDispatcher::Queues::TransceiverIdBuffer::TransceiverIdBuffer() {
    for (auto it = mBuffer.begin(); it != mBuffer.end(); ++it)
        *it = nullptr;
}

MessageDispatcher::Queues::TransceiverIdBuffer::~TransceiverIdBuffer() {
    for (auto it = mBuffer.begin(); it != mBuffer.end(); ++it) {
        if (auto* id = *it; id && Message::checkTransceiver(*id))
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

}  // namespace ksys

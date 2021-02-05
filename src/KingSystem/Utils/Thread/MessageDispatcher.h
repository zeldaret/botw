#pragma once

#include <container/seadBuffer.h>
#include <container/seadObjList.h>
#include <heap/seadDisposer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Thread/Event.h"
#include "KingSystem/Utils/Thread/MessageDispatcherBase.h"
#include "KingSystem/Utils/Thread/MessageProcessor.h"
#include "KingSystem/Utils/UniqueArrayPtr.h"

namespace sead {
class Thread;
}

namespace ksys {

class Message;
class MessageProcessor;
struct MesTransceiverId;

class MessageQueue {
public:
    MessageQueue();
    virtual ~MessageQueue();
    virtual bool addMessage(const Message& message);
    virtual void processQueue(MessageProcessor& processor);
    virtual void clear();

private:
    Message* findUnusedEntry() const;

    util::UniqueArrayPtr<Message, 3000> mMessages;
};

class MessageDispatcher : public MessageDispatcherBase {
    SEAD_SINGLETON_DISPOSER(MessageDispatcher)
    SEAD_RTTI_OVERRIDE(MessageDispatcher, MessageDispatcherBase)
    MessageDispatcher() = default;
    ~MessageDispatcher() override;

public:
    struct InitArg {
        // TODO: rename
        int num1;
        int num2;
        int num_bools;
        bool set_instance;
    };

    void init(const InitArg& arg, sead::Heap* heap);

    bool isProcessingOnCurrentThread() const;

    void registerTransceiver(MessageReceiverEx& receiver) override;
    void deregisterTransceiver(MessageReceiverEx& receiver) override;
    bool sendMessage(const MesTransceiverId& src, const MesTransceiverId& dest,
                     const MessageType& type, void* user_data, bool ack, bool) override;
    bool sendMessageOnProcessingThread(const MesTransceiverId& src, const MesTransceiverId& dest,
                                       const MessageType& type, void* user_data, bool ack,
                                       bool) override;
    bool sendMessage(const MesTransceiverId& src, IMessageBrokerRegister& reg,
                     const MessageType& type, void* user_data, bool ack, bool) override;
    bool sendMessageOnProcessingThread(const MesTransceiverId& src, IMessageBrokerRegister& reg,
                                       const MessageType& type, void* user_data, bool ack,
                                       bool) override;
    void update() override;

private:
    friend struct AddMessageMainContext;

    class DoubleBufferedQueue {
    public:
        DoubleBufferedQueue();
        ~DoubleBufferedQueue();
        bool addMessage(const Message& message);
        void clear();
        void processQueue(MessageProcessor& processor);
        void swapBuffer() { mActiveIdx ^= 1; }
        MessageQueue* getQueue() { return &mBuffer[mActiveIdx ^ 1]; }

    private:
        u32 mActiveIdx = 1;
        MessageQueue mBuffer[2];
    };

    class MainQueue {
    public:
        MainQueue();
        virtual ~MainQueue();
        virtual bool addMessage(const Message& message);
        virtual void clear();
        virtual void processQueue(MessageProcessor& processor);

    private:
        DoubleBufferedQueue mQueue;
        bool mHasMessageToProcess = false;
    };

    class Queues {
    public:
        explicit Queues(MessageProcessor::Logger* logger);
        ~Queues();
        const u32& getId() const { return mId; }
        sead::CriticalSection& getCritSection() { return mCritSection; }
        const auto& getIdPointers() const { return mTransceiverIdPtrs.mBuffer; }
        DoubleBufferedQueue& getQueue() { return mQueue; }
        MainQueue& getMainQueue() { return mMainQueue; }
        bool isProcessing() const { return mIsProcessing; }
        void process();
        bool sendMessageOnProcessingThread(const MesTransceiverId& src,
                                           const MesTransceiverId& dest, const MessageType& type,
                                           void* user_data, bool ack);

    private:
        struct DummyLogger : public MessageProcessor::Logger {
            ~DummyLogger() override;
            void log(const Message& message, bool success) override {}
        };

        struct TransceiverIdBuffer {
            TransceiverIdBuffer();
            ~TransceiverIdBuffer();

            util::UniqueArrayPtr<MesTransceiverId*, 10000> mBuffer;
        };

        sead::CriticalSection mCritSection;
        u32 mId = 0xffffffff;
        DummyLogger mDummyLogger;
        TransceiverIdBuffer mTransceiverIdPtrs;
        DoubleBufferedQueue mQueue;
        MainQueue mMainQueue;
        MessageProcessor mProcessor;
        bool mIsProcessing = false;
    };

    enum class Flag {
        Initialized = 1 << 0,
    };

    struct Logger : MessageProcessor::Logger {
        ~Logger() override;
        void log(const Message& message, bool success) override;
    };

    sead::Thread* mProcessingThread{};
    Logger mLogger{};
    Queues* mQueues{};
    sead::TypedBitFlag<Flag> mFlags;
    sead::Buffer<u8> mBoolBuffer;
    sead::ObjList<u8*> mBools;
    sead::CriticalSection mCritSection;
    util::Event mUpdateEndEvent;
    sead::Atomic<int> mNumEntries = 0;
};

}  // namespace ksys

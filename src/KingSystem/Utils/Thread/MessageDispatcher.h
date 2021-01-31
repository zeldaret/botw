#pragma once

#include <container/seadBuffer.h>
#include <container/seadObjList.h>
#include <heap/seadDisposer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
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
                     const MessageType& type, void* user_data, bool ack) override;
    bool sendMessageOnProcessingThread(const MesTransceiverId& src, const MesTransceiverId& dest,
                                       const MessageType& type, void* user_data, bool ack) override;
    void m_8() override;
    void m_9() override;
    void update() override;

private:
    class Queue {
    public:
        Queue();
        virtual ~Queue();
        virtual bool addMessage(const Message& message);
        virtual void processQueue(MessageProcessor& processor);
        virtual void clear();

    private:
        Message* findUnusedEntry() const;

        util::UniqueArrayPtr<Message, 3000> mMessages;
    };

    class DoubleBufferedQueue {
    public:
        DoubleBufferedQueue();
        ~DoubleBufferedQueue();
        bool addMessage(const Message& message);
        void clear();
        void processQueue(MessageProcessor& processor);

    private:
        u32 mActiveIdx = 1;
        Queue mBuffer[2];
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
        TransceiverIdBuffer mTransceiverIds;
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
    sead::Buffer<bool> mBoolBuffer;
    sead::ObjList<bool*> mBools;
    sead::CriticalSection mCritSection;
    util::Event mUpdateEndEvent;
    int mNumEntries = 0;
};

}  // namespace ksys

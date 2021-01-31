#pragma once

#include <basis/seadTypes.h>
#include <tuple>
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace ksys {

struct MessageType {
    MessageType() = default;
    MessageType(u32 v) : value(v) {}  // NOLINT(google-explicit-constructor)

    u32 value;
};

class MessageDelayer {
public:
    MessageDelayer() = default;
    virtual ~MessageDelayer() = default;
    virtual bool shouldProcessMessage() = 0;
};

class Message {
public:
    struct DelayParams {
        DelayParams() : delay_ticks(), delayer() {}
        DelayParams(const DelayParams& other) { *this = other; }
        // Yes, this operator is quite pointless, but we need it to match.
        DelayParams& operator=(const DelayParams& other) {
            delay_ticks = other.delay_ticks;
            delayer = other.delayer;
            return *this;
        }

        int delay_ticks;
        MessageDelayer* delayer;
    };

    Message();
    Message(const Message& message) { *this = message; }
    Message(const MesTransceiverId& source, const MesTransceiverId& destination,
            const MessageType& type, void* user_data, const DelayParams& delay_params, bool ack);
    Message(const MesTransceiverId& source, const MessageType& type, void* user_data,
            const DelayParams& delay_params, bool ack);

    virtual ~Message();

    Message& operator=(const Message& other) {
        mSource = other.getSource();
        mDestination = other.getDestination();
        mType = other.getType();
        mUserData = other.getUserData();
        _48 = other.getField48();
        mDelayParams = other.mDelayParams;
        mShouldAck = other.shouldAck();
        return *this;
    }

    virtual const MesTransceiverId& getSource() const;
    virtual const MesTransceiverId& getDestination() const;
    virtual const MessageType& getType() const;
    virtual void* getUserData() const;
    virtual u32 getField48() const;
    virtual bool shouldAck() const;
    virtual void setDestination(const MesTransceiverId& dest);
    virtual void setField48(const u32& v);
    virtual bool shouldBeProcessed() const;

    bool hasDelayer() const { return mDelayParams.delayer != nullptr; }

    void decrementDelay() {
        if (mDelayParams.delay_ticks != 0)
            --mDelayParams.delay_ticks;
    }

    void reset() {
        mType = {};
        mUserData = {};
        _48 = 0xffffffff;
        mDelayParams = {};
        mShouldAck = {};
        mSource.reset();
        mDestination.reset();
    }

    void resetIfValid() {
        if (isValid())
            reset();
    }

    bool isValid() const { return checkTransceiver(mDestination); }

    static bool checkTransceiver(const MesTransceiverId& id) {
        if (!id.next)
            return false;

        MesTransceiverId* next = *id.next;
        if (!next)
            return false;

        const auto& fields = [](const MesTransceiverId& i) { return std::tie(i.queue_id, i.id); };
        return fields(id) == fields(*next);
    }

private:
    MesTransceiverId mSource{};
    MesTransceiverId mDestination{};
    MessageType mType{};
    void* mUserData{};
    u32 _48 = 0xffffffff;
    DelayParams mDelayParams{};
    bool mShouldAck = true;
};

}  // namespace ksys

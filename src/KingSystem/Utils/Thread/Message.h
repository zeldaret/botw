#pragma once

#include <basis/seadTypes.h>

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
    Message(const MesTransceiverId& source, const MesTransceiverId& destination,
            const MessageType& type, void* user_data, const DelayParams& delay_params, bool x);
    Message(const MesTransceiverId& source, const MessageType& type, void* user_data,
            const DelayParams& delay_params, bool x);

    virtual ~Message();

    virtual const MesTransceiverId& getSource() const;
    virtual const MesTransceiverId& getDestination() const;
    virtual const MessageType& getType() const;
    virtual void* getUserData() const;
    virtual u32 getField48() const;
    virtual bool getField60() const;
    virtual void setDestination(const MesTransceiverId& dest);
    virtual void setField48(const u32& v);
    virtual bool shouldBeProcessed() const;

private:
    MesTransceiverId mSource{};
    MesTransceiverId mDestination{};
    MessageType mType{};
    void* mUserData{};
    u32 _48 = 0xffffffff;
    DelayParams mDelayParams{};
    bool _60 = true;
};

}  // namespace ksys

#include "KingSystem/Utils/Thread/Message.h"

namespace ksys {

Message::Message() = default;

Message::Message(const MesTransceiverId& source, const MesTransceiverId& destination,
                 const MessageType& type, void* user_data, const Message::DelayParams& delay_params,
                 bool ack)
    : mSource(source), mDestination(destination), mType(type), mUserData(user_data),
      mDelayParams(delay_params), mShouldAck(ack) {}

Message::Message(const MesTransceiverId& source, const MessageType& type, void* user_data,
                 const Message::DelayParams& delay_params, bool ack)
    : mSource(source), mType(type), mUserData(user_data), mDelayParams(delay_params),
      mShouldAck(ack) {}

Message::~Message() = default;

const MesTransceiverId& Message::getSource() const {
    return mSource;
}

const MesTransceiverId& Message::getDestination() const {
    return mDestination;
}

const MessageType& Message::getType() const {
    return mType;
}

void* Message::getUserData() const {
    return mUserData;
}

u32 Message::getBrokerId() const {
    return mBrokerId;
}

bool Message::shouldBeProcessed() const {
    if (mDelayParams.delay_ticks != 0)
        return false;

    if (!mDelayParams.delayer)
        return true;

    return mDelayParams.delayer->shouldProcessMessage();
}

bool Message::shouldAck() const {
    return mShouldAck;
}

void Message::setDestination(const MesTransceiverId& dest) {
    mDestination = dest;
}

void Message::setBrokerId(const u32& v) {
    mBrokerId = v;
}

}  // namespace ksys

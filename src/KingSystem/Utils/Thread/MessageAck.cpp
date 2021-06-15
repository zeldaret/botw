#include "KingSystem/Utils/Thread/MessageAck.h"

namespace ksys {

MessageAck::MessageAck(bool dest_valid, bool success, const MesTransceiverId& destination,
                       const MessageType& type, void* user_data)
    : mDestValid(dest_valid), mSuccess(success), mDestination(destination), mType(type),
      mUserData(user_data) {}

MessageAck::~MessageAck() = default;

bool MessageAck::isDestinationValid() const {
    return mDestValid;
}

bool MessageAck::isSuccess() const {
    return mSuccess;
}

const MesTransceiverId& MessageAck::getDestination() const {
    return mDestination;
}

const MessageType& MessageAck::getType() const {
    return mType;
}

void* MessageAck::getUserData() const {
    return mUserData;
}

}  // namespace ksys

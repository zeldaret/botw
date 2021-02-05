#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/MessageTransceiverCommon.h"

namespace ksys {

ActorMessageTransceiver::ActorMessageTransceiver(IHandler& handler) : mReceiver(handler) {
    registerReceiver(mReceiver);
}

ActorMessageTransceiver::ActorMessageTransceiver(IHandler& handler, act::Actor* actor)
    : mReceiver(handler), mActor(actor) {
    registerReceiver(mReceiver);
}

ActorMessageTransceiver::~ActorMessageTransceiver() {
    deregisterReceiver(mReceiver);
}

bool ActorMessageTransceiver::getDebugArg(bool ack) const {
    return mActor && mActor->checkFlag(act::Actor::ActorFlag::_2e) && ack;
}

bool ActorMessageTransceiver::sendMessage(const MesTransceiverId& dest, const MessageType& type,
                                          void* user_data, bool ack) {
    return sendMessageImpl(this, dest, type, user_data, ack, getDebugArg(ack));
}

bool ActorMessageTransceiver::sendMessageOnProcessingThread(const MesTransceiverId& dest,
                                                            const MessageType& type,
                                                            void* user_data, bool ack) {
    return sendMessageOnProcessingThreadImpl(this, dest, type, user_data, ack, getDebugArg(ack));
}

bool ActorMessageTransceiver::sendMessage(IMessageBroker& broker, const MessageType& type,
                                          void* user_data, bool ack) {
    return sendMessageImpl(this, broker, type, user_data, ack, getDebugArg(ack));
}

bool ActorMessageTransceiver::sendMessageOnProcessingThread(IMessageBroker& broker,
                                                            const MessageType& type,
                                                            void* user_data, bool ack) {
    return sendMessageOnProcessingThreadImpl(this, broker, type, user_data, ack, getDebugArg(ack));
}

MessageReceiverEx* ActorMessageTransceiver::getReceiver() {
    return &mReceiver;
}

ActorMessageTransceiver::Receiver::Receiver(IHandler& handler) : mHandler(handler) {}

ActorMessageTransceiver::Receiver::~Receiver() = default;

int ActorMessageTransceiver::Receiver::handleMessage(const Message& message) {
    return mHandler.handleMessage(message);
}

void ActorMessageTransceiver::Receiver::handleAck(const MessageAck& ack) {
    return mHandler.handleAck(ack);
}

}  // namespace ksys

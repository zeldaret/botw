#include "KingSystem/Utils/Thread/MessageProcessor.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageAck.h"
#include "KingSystem/Utils/Thread/MessageReceiver.h"

namespace ksys {

MessageProcessor::MessageProcessor(Logger* logger) : mLogger(logger) {}

MessageProcessor::~MessageProcessor() = default;

bool MessageProcessor::process(Message* message) {
    message->decrementDelay();

    if (!message->shouldBeProcessed())
        return false;

    bool success = false;
    bool dest_valid = false;

    const auto& dest = message->getDestination();
    if (dest.isRegistered()) {
        success = dest.receiver->receive(*message) & 1;
        mLogger->log(*message, success);
        dest_valid = true;
    }

    const auto& src = message->getSource();
    if (!message->hasDelayer() || src.isRegistered()) {
        if (message->shouldAck()) {
            const auto& source = message->getSource();
            if (source.isRegistered()) {
                auto* receiver = source.receiver;
                const MessageAck ack{dest_valid, success, message->getDestination(),
                                     message->getType(), message->getUserData()};
                receiver->receive(ack);
            }
        }
    } else {
        mLogger->log(*message, false);
    }

    return true;
}

}  // namespace ksys

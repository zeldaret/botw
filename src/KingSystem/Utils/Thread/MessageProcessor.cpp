#include "KingSystem/Utils/Thread/MessageProcessor.h"
#include <tuple>
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageAck.h"
#include "KingSystem/Utils/Thread/MessageReceiver.h"

namespace ksys {

MessageProcessor::MessageProcessor(Logger* logger) : mLogger(logger) {}

MessageProcessor::~MessageProcessor() = default;

static bool checkTransceiver(const MesTransceiverId& id) {
    if (!id.next)
        return false;

    MesTransceiverId* next = *id.next;
    if (!next)
        return false;

    const auto& fields = [](const MesTransceiverId& i) { return std::tie(i.queue_id, i.id); };
    return fields(id) == fields(*next);
}

bool MessageProcessor::process(Message* message) {
    message->decrementDelay();

    if (!message->shouldBeProcessed())
        return false;

    bool success = false;
    bool dest_valid = false;

    const auto& dest = message->getDestination();
    if (checkTransceiver(dest)) {
        success = dest.receiver->receive(*message) & 1;
        mLogger->log(*message, success);
        dest_valid = true;
    }

    const auto& src = message->getSource();
    if (!message->hasDelayer() || checkTransceiver(src)) {
        if (message->shouldAck()) {
            const auto& source = message->getSource();
            if (checkTransceiver(source)) {
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

#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace ksys {

class Message;
class MessageAck;

class MessageReceiver {
public:
    MessageReceiver();
    virtual ~MessageReceiver();
    virtual MesTransceiverId* getId();
    virtual int receive(const Message& message);
    virtual void receive(const MessageAck& ack);
    virtual void setQueueId(const u32& id) { mTransceiverId.queue_id = id; }

protected:
    MesTransceiverId mTransceiverId;

private:
    static u32 sId;
};

}  // namespace ksys

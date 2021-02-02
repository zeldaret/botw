#pragma once

#include <basis/seadTypes.h>

namespace ksys {

class IMessageBroker;
class IMessageBrokerRegister;
class MessageDispatcherBase;
struct MesTransceiverId;
class MessageReceiverEx;

class MessageTransceiverBase {
public:
    MessageTransceiverBase();
    virtual ~MessageTransceiverBase();
    bool checkReceiverFlag() const;
    bool checkReceiverCounter() const;
    virtual bool m2();
    virtual bool m3();
    virtual bool m4();
    virtual bool m5();
    virtual MessageReceiverEx* getReceiver() const = 0;
    MessageDispatcherBase* getDispatcher();
    MesTransceiverId* getId() const { return mId; }
    IMessageBrokerRegister* getRegister(IMessageBroker& broker) const;

    static void setGlobalDispatcher(MessageDispatcherBase* dispatcher);

private:
    static MessageDispatcherBase* sDispatcher;

    MessageDispatcherBase* mDispatcher = sDispatcher;
    MesTransceiverId* mId{};
};

}  // namespace ksys

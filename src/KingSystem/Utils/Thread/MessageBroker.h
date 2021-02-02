#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys {

class Message;
class MessageTransceiverBase;
class MessageQueue;
struct MesTransceiverId;

class IMessageBrokerRegister {
public:
    struct IForEachContext {
        virtual ~IForEachContext() = default;
        virtual void process(const MesTransceiverId& id) = 0;
    };

    virtual ~IMessageBrokerRegister() = default;
    virtual bool registerTransceiver(const MesTransceiverId& id) = 0;
    virtual void deregisterTransceiver(const MesTransceiverId& id) = 0;
    virtual void forEachRegistered(IForEachContext& context) = 0;
    virtual void setId(const u32& id) = 0;
    virtual const u32& getId() const = 0;
    virtual int countTransceivers() const = 0;
};

class IMessageBroker {
public:
    class SetIdArg {
        SEAD_RTTI_BASE(SetIdArg)
    public:
        SetIdArg() = default;
        explicit SetIdArg(u32 id) { setId(id); }
        virtual ~SetIdArg() = default;
        u32 getId() const { return mId; }
        void setId(u32 id) { mId = id; }

    private:
        u32 mId{};
    };

    IMessageBroker();
    virtual ~IMessageBroker();
    virtual void setId(const SetIdArg& arg) = 0;
    virtual IMessageBrokerRegister* getRegister() = 0;
    bool registerTransceiver(const MessageTransceiverBase& transceiver);
    void deregisterTransceiver(const MessageTransceiverBase& transceiver);
    int countTransceivers();
};

}  // namespace ksys

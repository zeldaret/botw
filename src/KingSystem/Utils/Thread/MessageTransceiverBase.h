#pragma once

#include <basis/seadTypes.h>

namespace ksys {

class MessageDispatcherBase;
struct MesTransceiverId;
class MesTransceiverIdGenEx;

class MessageTransceiverBase {
public:
    MessageTransceiverBase();
    virtual ~MessageTransceiverBase();
    bool checkGeneratorFlag() const;
    bool checkGeneratorCounter() const;
    virtual bool m2();
    virtual bool m3();
    virtual bool m4();
    virtual bool m5();
    virtual MesTransceiverIdGenEx* getGenerator() const = 0;
    MessageDispatcherBase* getDispatcher();

    static void setGlobalDispatcher(MessageDispatcherBase* dispatcher);

private:
    static MessageDispatcherBase* sDispatcher;

    MessageDispatcherBase* mDispatcher = sDispatcher;
    MesTransceiverId* mId{};
};

}  // namespace ksys

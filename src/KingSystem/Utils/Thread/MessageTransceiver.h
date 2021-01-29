#pragma once

#include <basis/seadTypes.h>

namespace ksys {

class MessageDispatcherBase;
struct MesTransceiverId;

class MessageTransceiver {
public:
    MessageTransceiver();
    virtual ~MessageTransceiver();
    bool checkX();
    bool checkY();
    virtual bool m2();
    virtual bool m3();
    virtual bool m4();
    virtual bool m5();
    virtual void* getSomePtr() = 0;
    MessageDispatcherBase* getDispatcher();

    static void setGlobalDispatcher(MessageDispatcherBase* dispatcher);

private:
    static MessageDispatcherBase* sDispatcher;

    MessageDispatcherBase* mDispatcher = sDispatcher;
    MesTransceiverId* mId{};
};

}  // namespace ksys

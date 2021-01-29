#pragma once

#include <prim/seadRuntimeTypeInfo.h>

namespace ksys {

class MessageDispatcherBase {
    SEAD_RTTI_BASE(MessageDispatcherBase)
public:
    MessageDispatcherBase();
    virtual ~MessageDispatcherBase();

    // TODO
    virtual void m_4() = 0;
    virtual void m_5() = 0;
    virtual void m_6() = 0;
    virtual void m_7() = 0;
    virtual void m_8() = 0;
    virtual void m_9() = 0;
    virtual void m_10() = 0;

protected:
    void setAsGlobalInstance();
};

}  // namespace ksys

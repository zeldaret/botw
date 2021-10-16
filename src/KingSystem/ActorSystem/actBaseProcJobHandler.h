#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actBaseProcJob.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProcJobHandler {
public:
    explicit BaseProcJobHandler(BaseProc* proc);
    virtual ~BaseProcJobHandler() = default;
    virtual void invoke() = 0;
    virtual void invokeSpecial() {}

    BaseProcJobLink& getLink() { return mLink; }
    const BaseProcJobLink& getLink() const { return mLink; }

protected:
    BaseProcJobLink mLink;
};
KSYS_CHECK_SIZE_NX150(BaseProcJobHandler, 0x30);

/// For binding actor member functions.
template <typename T>
class BaseProcJobHandlerT : public BaseProcJobHandler {
public:
    BaseProcJobHandlerT(T* proc, void (T::*fn)()) : BaseProcJobHandler(proc), mDelegate(proc, fn) {}

    void invoke() override { mDelegate.invoke(); }

private:
    sead::Delegate<T> mDelegate;
};

/// For binding two actor member functions.
template <typename T>
class BaseProcJobHandlerDualT : public BaseProcJobHandler {
public:
    BaseProcJobHandlerDualT(T* proc, void (T::*fn)(), void (T::*fn_special)())
        : BaseProcJobHandler(proc), mDelegate(proc, fn), mDelegateSpecial(proc, fn_special) {}

    void invoke() override { mDelegate.invoke(); }
    void invokeSpecial() override { mDelegateSpecial.invoke(); }

private:
    sead::Delegate<T> mDelegate;
    sead::Delegate<T> mDelegateSpecial;
};

}  // namespace ksys::act

#pragma once

#include <heap/seadDisposer.h>

namespace ksys::act {

struct ActorCreateArg;
class BaseProc;

class ActorFactory {
public:
    virtual void dummy();
    virtual BaseProc* createActor(const ActorCreateArg& arg);
    virtual void dummy2();
};

class ActorFactoryHolder {
    SEAD_SINGLETON_DISPOSER(ActorFactoryHolder)
    ActorFactoryHolder() = default;
    virtual ~ActorFactoryHolder();

public:
    void init(sead::Heap* heap);

private:
    ActorFactory mFactory;
};

}  // namespace ksys::act

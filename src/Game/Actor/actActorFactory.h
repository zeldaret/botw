#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/ActorSystem/actActorCreator.h"

namespace uking::act {

class ActorFactory : public ksys::act::IActorFactory {
public:
    void dummy() override;
    ksys::act::BaseProc* createActor(const ksys::act::ActorCreateArg& arg) override;
    void dummy2() override;
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

}  // namespace uking::act

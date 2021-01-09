#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Resource/resHandle.h"

namespace ksys::res {
class GParamListObjectGlobal;
}

namespace ksys::act {

class ActorParam;

class GlobalParameter {
    SEAD_SINGLETON_DISPOSER(GlobalParameter)
    GlobalParameter() = default;
    ~GlobalParameter() = default;

public:
    bool init(sead::Heap* heap);
    void finalize();

    void loadActorPack(sead::Heap* heap);
    bool isActorPackReady() const;
    bool loadActorParams();

    const res::GParamListObjectGlobal* getGlobalParam() const { return mGlobalParam; }

private:
    bool loadActorParams_();

    ActorParam* mActorParam{};
    const res::GParamListObjectGlobal* mGlobalParam{};
    res::Handle mResHandle{};
};

}  // namespace ksys::act

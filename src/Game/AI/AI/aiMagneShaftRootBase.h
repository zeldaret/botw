#pragma once

#include "Game/AI/AI/aiMagneStickRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MagneShaftRootBase : public MagneStickRoot {
    SEAD_RTTI_OVERRIDE(MagneShaftRootBase, MagneStickRoot)
public:
    explicit MagneShaftRootBase(const InitArg& arg);
    ~MagneShaftRootBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

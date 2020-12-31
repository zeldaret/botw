#pragma once

#include "Game/AI/AI/aiMagneShaftRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MagneShaftRoot : public MagneShaftRootBase {
    SEAD_RTTI_OVERRIDE(MagneShaftRoot, MagneShaftRootBase)
public:
    explicit MagneShaftRoot(const InitArg& arg);
    ~MagneShaftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

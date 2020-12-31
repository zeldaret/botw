#pragma once

#include "Game/AI/AI/aiMagneShaftRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MagneSliderBlockRootThunder : public MagneShaftRootBase {
    SEAD_RTTI_OVERRIDE(MagneSliderBlockRootThunder, MagneShaftRootBase)
public:
    explicit MagneSliderBlockRootThunder(const InitArg& arg);
    ~MagneSliderBlockRootThunder() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

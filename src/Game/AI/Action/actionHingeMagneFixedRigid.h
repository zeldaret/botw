#pragma once

#include "Game/AI/Action/actionFixedMagneSliderBlock.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HingeMagneFixedRigid : public FixedMagneSliderBlock {
    SEAD_RTTI_OVERRIDE(HingeMagneFixedRigid, FixedMagneSliderBlock)
public:
    explicit HingeMagneFixedRigid(const InitArg& arg);
    ~HingeMagneFixedRigid() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action

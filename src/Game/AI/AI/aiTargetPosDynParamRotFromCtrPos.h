#pragma once

#include "Game/AI/AI/aiTargetPosDynParamRot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosDynParamRotFromCtrPos : public TargetPosDynParamRot {
    SEAD_RTTI_OVERRIDE(TargetPosDynParamRotFromCtrPos, TargetPosDynParamRot)
public:
    explicit TargetPosDynParamRotFromCtrPos(const InitArg& arg);
    ~TargetPosDynParamRotFromCtrPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x58
    sead::Vector3f* mCenterPos_d{};
};

}  // namespace uking::ai

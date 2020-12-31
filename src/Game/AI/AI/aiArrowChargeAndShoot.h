#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ArrowChargeAndShoot : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(ArrowChargeAndShoot, SeqTwoAction)
public:
    explicit ArrowChargeAndShoot(const InitArg& arg);
    ~ArrowChargeAndShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const int* mWeaponIdx_s{};
};

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossSwordWhirlSlash : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossSwordWhirlSlash, ksys::act::ai::Ai)
public:
    explicit LastBossSwordWhirlSlash(const InitArg& arg);
    ~LastBossSwordWhirlSlash() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    bool* mIsNoCharge_d{};
};

}  // namespace uking::ai

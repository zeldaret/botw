#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRoamSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRoamSelect, ksys::act::ai::Ai)
public:
    explicit EnemyRoamSelect(const InitArg& arg);
    ~EnemyRoamSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mHideGrassHeight_s{};
    // static_param at offset 0x40
    const float* mNotReturnDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mCentralPos_d{};
};

}  // namespace uking::ai

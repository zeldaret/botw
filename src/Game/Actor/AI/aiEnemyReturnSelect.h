#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyReturnSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyReturnSelect, ksys::act::ai::Ai)
public:
    explicit EnemyReturnSelect(const InitArg& arg);
    ~EnemyReturnSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mNotReturnDist_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mCentralPos_d{};
};

}  // namespace uking::ai
